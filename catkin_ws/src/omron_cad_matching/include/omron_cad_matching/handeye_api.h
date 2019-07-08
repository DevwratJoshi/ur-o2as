// *********************************************************************
//              (C) Copyright OMRON CORPORATION 2017
//                        All Rights Reserved
// ---------------------------------------------------------------------
//               �n���h�A�C�L�����u���[�V����(HANDEYE)���C�u����
// *********************************************************************
// �t �@ �C �� �� : handeye_api.h
// ��  ��  �T  �v : �n���h�A�C�L�����u���[�V����API�֐��̒�`
// �Q  �l  ��  �� : 1) Daniilidis, Konstantinos. "Hand-eye calibration using dual quaternions."
//                      The International Journal of Robotics Research 18.3 (1999): 286-298.
// *********************************************************************

#ifndef MBP_HANDEYE_API_H_
#define MBP_HANDEYE_API_H_

// *************************************
//         �C���N���[�h�t�@�C��         
// *************************************
#include "mbp_api.h"

// for DLL compile
#ifdef _USRDLL
#if defined( __cplusplus )
#define HANDEYE_API extern "C" __declspec (dllexport)
extern "C" {
#else
#define HANDEYE_API __declspec (dllexport)
#endif

#else
// for STLIB compile
#if defined( __cplusplus )
extern "C" {
#endif
#define HANDEYE_API
#endif

	// �n���h�A�C�L�����u���[�V�����̌��ʍ\����
	typedef struct tagMBPHandEyeResult
	{
		// �Œ�J�����FSen->Rob
		// �n���h���ڃJ�����FSen->Tol
		double rot_mat_sen[9];				// ��]�s��
		double handeye_angle_trans_sen[6];	// ���� 0:X����]�p�x,1:Y����]�p�x,2:Z����]�p�x,3:Tx,4:Ty,5:Tz
		double eval_error_sen[6];			// �]���덷 0:X����]�p�x,1:Y����]�p�x,2:Z����]�p�x,3:Tx,4:Ty,5:Tz

		// �Œ�J�����FObj->Tol
		// �n���h���ڃJ�����FObj->Rob
		double rot_mat_obj[9];				// ��]�s��
		double handeye_angle_trans_obj[6];	// ���� 0:X����]�p�x,1:Y����]�p�x,2:Z����]�p�x,3:Tx,4:Ty,5:Tz
		double eval_error_obj[6];			// �]���덷 0:X����]�p�x,1:Y����]�p�x,2:Z����]�p�x,3:Tx,4:Ty,5:Tz
	}  HANDEYE_HandEyeResult;

	// �Œ�J�����̃p�����[�^�\����
	typedef struct tagFixedCamSetting
	{
		// �V�X�e�����ݒ�
		float cam_org_in_base[3];	// �x�[�X���W�n����Z���T���W�n�ւ̕��i�x�N�g�� [mm]
		float cam_xaxis_in_base[3];	// �x�[�X���W�n�Ō����Z���T���W�nX�������x�N�g��
		float cam_zaxis_in_base[3];	// �x�[�X���W�n�Ō����Z���T���W�nZ�������x�N�g��
		float init_angle_J6;		// J6�̏����p�x [deg]
		float targ_org_in_tool[3];	// �c�[�����W�n�Ō����^�[�Q�b�g���_�ʒu [mm]

		// ����ݒ�
		INT32 num_x;				// X�̃T���v����
		INT32 num_y;				// Y�̃T���v����
		INT32 num_z;				// Z�̃T���v����

		// ����͈�
		float near_rectangle_center[3];	// �Z���T�Ɉ�ԋ߂��ʂ̓��쒆�S [mm]
		float operation_range_size[3];	// ����͈� [mm]

		float perturb_rot_angle[3];	// �Z���T���W�n�̐ۓ��p�x [deg]
	} HANDEYE_FixedCamSetting;

	// �n���h���ڃJ�����̃p�����[�^�\����
	typedef struct tagMovingCamSetting
	{
		// �V�X�e�����ݒ�
		float trans_targ2base[3];	// ���{�b�g�x�[�X���猩���^�[�Q�b�g�̂R�����ʒu���W [mm]
		float cam_org_in_tool[3];	// �c�[�����W�n���猩���Z���T���W�n���_�̈ʒu [mm]
		float cam_xaxis_in_tool[3];	// �c�[�����W�n���猩���Z���T���W�n��X������
		float cam_zaxis_in_tool[3];	// �c�[�����W�n���猩���Z���T���W�n��Z������

		// ����ݒ�
		INT32 num_radius;			// ���a�̃T���v����
		INT32 num_theta;			// �Ɋp�̃T���v����
		INT32 num_phi;				// ���ʊp�̃T���v����
		float *pos_radius;			// ���a�ʒu(num_radius��) [mm]
		float *pos_theta;			// �Ɋp(num_theta��) [deg]
		float *pos_phi;				// ���ʊp(num_phi��) [deg]

		// �ۓ��ʁi�^�[�Q�b�g���W�n�ł̃Z���T�ʒu�p���̐ۓ��ʁj
		INT32 delta_rot_x;			// �p�xx [deg]
		INT32 delta_rot_y;			// �p�xy [deg]
		INT32 delta_rot_z;			// �p�xz [deg]
		INT32 delta_pos_x;			// �ʒux [mm]
		INT32 delta_pos_y;			// �ʒuy [mm]
		INT32 delta_pos_z;			// �ʒuz [mm]
	} HANDEYE_MovingCamSetting;

	// *************************************
	//         �v���g�^�C�v�֐��錾        
	// *************************************
	// ��v�֐�
	HANDEYE_API MBP_ERR_CODE HANDEYE_CalibrateFixedCam(const INT32 sample_num, const double *robot_pose_angle, const double *robot_pose_trans, const double *target_pose_angle, const double *target_pose_trans, HANDEYE_HandEyeResult *handeye_result);
	HANDEYE_API MBP_ERR_CODE HANDEYE_CalibrateFixedCamWithKnownTcp(const INT32 sample_num, const double *robot_pose_angle, const double *robot_pose_trans, const double *target_pose_angle, const double *target_pose_trans, HANDEYE_HandEyeResult *handeye_result);
	HANDEYE_API MBP_ERR_CODE HANDEYE_CalibrateMovingCam(const INT32 sample_num, const double *robot_pose_angle, const double *robot_pose_trans, const double *target_pose_angle, const double *target_pose_trans, HANDEYE_HandEyeResult *handeye_result);
	HANDEYE_API MBP_ERR_CODE HANDEYE_Evaluate(const INT32 sample_num, const double *robot_pose_angle, const double *robot_pose_trans, const double *target_pose_angle, const double *target_pose_trans, const HANDEYE_HandEyeResult *handeye_param_compared, const BOOL is_fixed_cam, double eval_error[6], double *predictedpose_rot_mat, double *predictedpose_trans_vec);
	HANDEYE_API MBP_ERR_CODE HANDEYE_MakeRobotPoseFixedCam(const HANDEYE_FixedCamSetting *setting, float *angle_tool2base, float *trans_tool2base);	// �Œ�J�����ňʒu�p������
	HANDEYE_API MBP_ERR_CODE HANDEYE_MakeRobotPoseMovingCam(const HANDEYE_MovingCamSetting *setting, float *angle_tool2base, float *trans_tool2base);	// �n���h���ڃJ�����ňʒu�p������

	// �������A�������֘A
	HANDEYE_API MBP_ERR_CODE HANDEYE_AllocHandEyeResult(HANDEYE_HandEyeResult **handeye_result);
	HANDEYE_API MBP_ERR_CODE HANDEYE_DeleteHandEyeResult(HANDEYE_HandEyeResult **handeye_result);
	HANDEYE_API MBP_ERR_CODE HANDEYE_AllocFixedCamSetting(HANDEYE_FixedCamSetting **setting);
	HANDEYE_API MBP_ERR_CODE HANDEYE_DeleteFixedCamSetting(HANDEYE_FixedCamSetting **setting);
	HANDEYE_API MBP_ERR_CODE HANDEYE_AllocMovingCamSetting(HANDEYE_MovingCamSetting **setting);
	HANDEYE_API MBP_ERR_CODE HANDEYE_DeleteMovingCamSetting(HANDEYE_MovingCamSetting **setting);

	// �T�u����
	HANDEYE_API MBP_ERR_CODE HANDEYE_GetVersion(char *major, char *minor, char *sub_minor);	// ���C�u�����[�o�[�W�����̎擾
	HANDEYE_API char*        HANDEYE_GetErrorMessage(const INT32 error_code);

#if defined( __cplusplus )
}
#endif

#endif	/* MBP_HANDEYE_API_H_ */
