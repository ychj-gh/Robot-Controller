/**
 *@brief 类 InterpolationDefault 默认插补类既定轨迹实现
 *  	 2017/12/11
 *  	 ychj
 */
#include "InterpolationDefault.h"

namespace RobotSpace{
	/*****************************************************************************/
	/**
 	* @brief 关节插补 unit: deg
 	* @param[in] originalPos 起始位置，角度 坐标系ACS
 	* @param[in] targetPos 目标位置，角度 坐标系ACS 
 	* @param[in] Ts 插补周期
 	* @param[in] velPerc 速度百分比（0.5-95.0，例如：设定以50%的最大速度运行，赋值50）
 	* @param[in] accPerc 加速度百分比（0.5-95.0）
 	* @param[in] jerkPerc 加加速度百分比
 	* @param[out] posSeq n组轴的位置插补（关节空间）序列，n为轴数 deg
 	* @return 若成功，返回 0
 	* @attention 注意入口参数单位为角度
 	*/
	/*****************************************************************************/
	int InterpolationDefault::JointInterp(const Position_ACS_deg& originalPos,
				const Position_ACS_deg& targetPos,double Ts,double velPerc,
				double accPerc,double jerkPerc ,std::deque<Position_ACS_deg>& posSeq)
	{
		std::cerr << "|>> ============= enter axis interp ===========>" << std::endl;
		std::cout << originalPos << std::endl;
		std::cout << targetPos << std::endl;
		size_t n = pRobot->getRobotAxisNum();
		Position_ACS_deg ChangePos = targetPos - originalPos;
		dvector t(n);
		double  Tmax = 0;
		dvector tA(n);
		double  Tacc = 0;

		// 计算实际百分比
		if(velPerc <= 0.5 || velPerc > 95.0)
		return 0 ;
		velPerc = velPerc / 100.0;
		if(accPerc <= 0.5 || accPerc > 95.0)
		return 0;
		accPerc = accPerc / 100.0; 

		// 找到最长运行时间
		for(size_t ai = 0; ai != n; ++ai)
			t[ai] = fabs(ChangePos[ai])/(velPerc * paramLim[ai].max_vel);
		Tmax = t[0];
		for(size_t ai = 1; ai != n; ++ai)
			if(Tmax < t[ai])    Tmax = t[ai];
		if(Tmax == 0)
		{
			std::cout << "No need to move !" << std::endl;
			return 0;
		}

		// 找到最长加速时间
		for(size_t ai = 0; ai != n; ++ai)
			tA[ai] = (velPerc * paramLim[ai].max_vel) / (accPerc * paramLim[ai].max_acc);
		Tacc = tA[0];
		for(size_t ai = 1; ai != n; ++ai)
			if(Tacc < tA[ai])		Tacc = tA[ai];
		if(Tacc == 0)
		{
			std::cout << "Tacc = 0" << std::endl;
			return 0;
		} 	

		// 计算每个轴的匀速段速度
		double tf = Tmax + Tacc;
		double Tconst = tf - 2 * Tacc;
		dvector velConst(n);

		if(Tconst < 0)
		{
			dvector Vmax(n);
			for(size_t ai = 0; ai != n; ++ai)
				Vmax[ai] = sqrt(fabs(ChangePos[ai]) * accPerc * paramLim[ai].max_acc);
			for(size_t ai = 0; ai != n; ++ai)
			{
				tA[ai] = Vmax[ai] / (accPerc * paramLim[ai].max_acc);
			}
			Tacc = tA[0];
			for(size_t ai = 1; ai != n; ++ai)
				if(Tacc < tA[ai])   Tacc = tA[ai];
			tf = 2 * Tacc;
			Tconst = 0;
			Tmax = Tacc;
			for(size_t ai = 0; ai != n; ++ai)
				velConst[ai] = ChangePos[ai] / Tacc;
		}
		else
			for(size_t ai = 0; ai != n; ++ai)
				velConst[ai] = ChangePos[ai] / Tmax;

		// 计算插补点
		size_t N1 = static_cast<size_t>(Tacc/Ts);
		size_t N2 = static_cast<size_t>(Tmax/Ts);
		size_t N3 = static_cast<size_t>(tf/Ts);

		// 计算加速段五次多项式系数
		dvector accPosEnd(n);
		std::vector<dvector> coeA(n);
		for(size_t ai = 0; ai != n; ++ai)
		{
			accPosEnd[ai] = originalPos[ai] + velConst[ai] * Tacc / 2.0;
			getQuinticCoe(originalPos[ai], accPosEnd[ai], 0, velConst[ai],0,0,Tacc,coeA[ai]);
		}

		// 计算减速段五次多项式系数
		dvector decPosStart(n);
		std::vector<dvector> coeD(n);
		for(size_t ai = 0; ai != n; ++ai)
		{
			decPosStart[ai] = accPosEnd[ai] + velConst[ai] * Tconst;
			getQuinticCoe(decPosStart[ai],targetPos[ai],velConst[ai],0,0,0,Tacc,coeD[ai]);
		}

		for(size_t i = 0; i != N3+1; ++i)
		{	
			Position_ACS_deg tmp(n);
			double t = i * Ts;  // Time
			if(i <= N1)
				for(size_t ai = 0; ai != n; ++ai)
					QuinticPolynomi(t,coeA[ai],tmp[ai]);
			else if(i <= N2)
				for(size_t ai = 0; ai != n; ++ai)
					tmp[ai] = accPosEnd[ai] + velConst[ai] * (t - Tacc);
			else if(i <= N3)
				for(size_t ai = 0; ai != n; ++ai)
					QuinticPolynomi(t-Tmax,coeD[ai],tmp[ai]);
			posSeq.push_back(tmp);
		}
		return 0;
	}


	/*****************************************************************************/
	/**
	 * @brief 位置控制模式下，笛卡尔坐标系下按直线插补 unit mm,rad
	 * @param[in] oriAxisPos 起始位置(ACS)， 弧度(关节) 
	 * @param[in] tarPos 目标位置，弧度(机器人末端在基坐标系下的位姿，若给定工具坐标系下位姿需要转换)
	 * @param[in] Ts 插补周期
	 * @param[in] maxVel 最大速度(机器人末端)
	 * @param[in] maxAcc 最大加速度(机器人末端)
	 * @param[in] maxDec 最大减速度(机器人末端)
	 * @param[in] maxJerk 最大加加速度(机器人末端)
	 * @param[in] oriVel 起始速度(机器人末端)
	 * @param[in] percVel 　速度百分比
	 * @param[out] posSeq n组轴的位置插补（关节空间）序列，n为轴数 deg
	 * @return 若成功，返回 0
	 * @attention 注意入口参数单位为弧度
	 * @todo 角速度限制
	 */
	/*****************************************************************************/
	int InterpolationDefault::LineInterp(const Position_ACS_rad& oriAxisPos, 
		const Position_MCS_rad& tarPos,double Ts, double maxVel, double maxAcc,double maxDec,
		double maxJerk,double oriVel,double percVel,std::deque<Position_ACS_deg>& posSeq)
	{
		std::cout << " 位置插补 " << std::endl;
		std::cout << " 初始位姿: " << oriAxisPos.transpose() << std::endl;
		size_t n = pRobot->getRobotAxisNum();
		Position_MCS_rad oriPos(6);
		int ret = pRobot->calcForwardKin_RPY(oriAxisPos,oriPos);
		if(ret) return -1;
		// if(coor == TOOL) 	frametrans(oriPos,tarPos);
		std::cout << " 初始位姿: " << oriPos.transpose() << std::endl;
		std::cout << " 目标位姿: " << tarPos.transpose() << std::endl;
		/******************************* 位置插补 ****************************************/
		double ox = oriPos[0],oy = oriPos[1], oz = oriPos[2];
		double tx = tarPos[0],ty = tarPos[1], tz = tarPos[2];
		double rundis = sqrt((ox-tx)*(ox-tx) + (oy-ty)*(oy-ty) + (oz-tz)*(oz-tz));
		// 计算加速时间
		double Vf = percVel / 100.0 * maxVel;
		double Tacc = 3 * fabs(Vf - oriVel) / (2 * maxAcc);
		double Tdec = 3 * Vf / (2 * maxAcc);
		double A_dis = maxAcc / 3 * Tacc * Tacc + oriVel * Tacc;
		double D_dis = maxAcc / 3 * Tdec * Tdec;
		double Tconst = (rundis - A_dis - D_dis) / Vf;
		std::vector<dvector> Pcoe(2);
		dvector  coe(6);
		coe << 0,oriVel,0, (2*maxAcc/(3*Tacc)), (-maxAcc/(3*Tacc*Tacc)),0;
		Pcoe[0] = coe;
		coe << (A_dis + Tconst*Vf) ,Vf,0, (-2*maxAcc / (3*Tdec)), (maxAcc/(3*Tdec*Tdec)),0;
		Pcoe[1] = coe;
		
		if(rundis < A_dis + D_dis)
		{
			Vf = sqrt(maxAcc * rundis);
			if(oriVel >= Vf)
			{	/* 只有减速段 */
				Tacc = 0;
				Tconst = 0;
				Tdec = 2 * oriVel / maxAcc;  // 加速度减半
				getQuinticCoe(0,rundis,oriVel,0,0,0,Tdec,Pcoe[1]);
			}
			else
			{	/* 加速度减半 */
				Vf = sqrt(0.5 * maxAcc * rundis + 0.5 * oriVel * oriVel);
				Tacc = 2 * (Vf - oriVel) / maxAcc;
				Tdec = 2 * Vf / maxAcc;
				Tconst = 0;
				A_dis = (oriVel + Vf) * Tacc / 2;
				std::cout << A_dis << std::endl;
				getQuinticCoe(0,A_dis,oriVel,Vf,0,0,Tacc,Pcoe[0]);
				getQuinticCoe(A_dis,rundis,Vf,0,0,0,Tdec,Pcoe[1]);
			}
		}
		double tf = Tacc + Tconst + Tdec;
		size_t N1 = static_cast<size_t> (Tacc/Ts);
		size_t N2 = static_cast<size_t> ((Tacc + Tconst)/Ts);
		size_t N3 = static_cast<size_t> (tf/Ts);

		std::cout << " 姿态插补 " << std::endl;
		/*******************************  姿态插补  ****************************************/
		std::vector<dvector> Acoe(3);
		double ofi = oriPos[3],otheta = oriPos[4], opusi = oriPos[5];
		double tfi = tarPos[3],ttheta = tarPos[4], tpusi = tarPos[5];
		if(tfi - ofi < -M_PI) 		tfi += 2*M_PI;
		else if(tfi - ofi > M_PI)	tfi -= 2*M_PI;
		if(ttheta-otheta < -M_PI)	ttheta += 2*M_PI;
		else if(ttheta-otheta >M_PI)	ttheta -= 2*M_PI;
		if(tpusi - opusi < -M_PI)	tpusi += 2*M_PI;
		else if(tpusi-opusi >M_PI)	tpusi -= 2*M_PI;
		getQuinticCoe(ofi,tfi,0,0,0,0,tf,Acoe[0]);
		getQuinticCoe(otheta,ttheta,0,0,0,0,tf,Acoe[1]);
		getQuinticCoe(opusi,tpusi,0,0,0,0,tf,Acoe[2]);
		

		std::cout << " 计算各个插补点 " << std::endl;
		Position_ACS_rad last_tmp(oriAxisPos);
		for(size_t i = 0; i != N3+1; ++i)
		{	
			/*******************************  计算各个插补点    ****************************************/	
			double t = i * Ts; 	 		// Time
			double dtmp;		 	 	// distance tmp
			Position_MCS_rad  Ttmp(6);		// TerminalPose tmp
			Position_ACS_rad  tmp(n);
			if(i <= N1)
				QuinticPolynomi(t,Pcoe[0],dtmp);
			else if(i <= N2)
				dtmp = A_dis + Vf * (t - Tacc);
			else if(i <= N3)
				QuinticPolynomi(t-Tacc-Tconst,Pcoe[1],dtmp);
			double r1 = dtmp / rundis;
			Ttmp[0] = (1 - r1) * ox + r1 * tx;
			Ttmp[1] = (1 - r1) * oy + r1 * ty;
			Ttmp[2] = (1 - r1) * oz + r1 * tz;
			QuinticPolynomi(t,Acoe[0],Ttmp[3]);
			QuinticPolynomi(t,Acoe[1],Ttmp[4]);
			QuinticPolynomi(t,Acoe[2],Ttmp[5]);

			/******************************* 计算路径上每个点的逆解　****************************************/	
			if(pRobot->calcInverseKin_RPY(Ttmp,last_tmp,tmp) == -1)
			{
				tmp = last_tmp;
				std::cout << " Can't move to target !" << std::endl;
				break;
			}
			last_tmp = tmp;
			posSeq.push_back(rad2deg(tmp));
		}

		std::cout << " oriPos ";
		std::cout << oriPos.transpose() << std::endl;
		std::cout << " tarPos ";
		std::cout << tarPos.transpose() << std::endl;
		std::cout << " Tacc = " << Tacc << "  Tconst =  " << Tconst << "  Tdec =  " << Tdec << std::endl;
		return 0;
	}

}