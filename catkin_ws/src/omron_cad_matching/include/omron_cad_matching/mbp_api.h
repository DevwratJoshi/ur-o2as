/*************************************************************************************/
/*
/*  MBP (MOGRA for Bin Picking)
/*  3D CAD Matching: 
/*  6D object pose estimation based on view-based template approach
/*
/*  Copyright (C) 2016, 2017  OMRON Corporation All rights reserved.
/*
/**************************************************************************************/

#ifndef MBP_API_H_
#define MBP_API_H_

// *************************************
//         �C���N���[�h�t�@�C��
// *************************************
//#include <windows.h>
#include "mbp_error.h"

// for DLL compile
#ifdef _USRDLL
#if defined( __cplusplus )
#define MBP_API extern "C" __declspec (dllexport)
extern "C" {
#else
#define MBP_API __declspec (dllexport)
#endif

// for STLIB compile
#else
#if defined( __cplusplus )
extern "C" {
#endif
#define MBP_API
#endif


// *************************************
//      �@�@�@�@�^��`
// *************************************
typedef void MBP_Mesh;
typedef void MBP_Meshes;
typedef void MBP_Box;

// *************************************
//     �@�@�@�@�񋓑̒�`
// *************************************
// ��Q���̎��
typedef enum tagMbpObstacle {
	MBP_OBSTACLE_BOX = 0,
	MBP_OBSTACLE_FLOOR = 1,
	MBP_OBSTACLE_NOTHING = 2
} e_MBP_Obstacle;

// ��]�p�x�̉�]��
typedef enum tagMbpRotAngleOrder
{
	MBP_ROTANGLE_XYZ = 0,
	MBP_ROTANGLE_ZYZ = 1,
} e_MBP_RotAngleOrder;

// *************************************
//      �@�@�@�@�\���̒�`
// *************************************
typedef struct tagMBPSetting
{
	INT32				width;					// �摜�� [pix]
	INT32				height;					// �摜���� [pix]
	float				cam_param[9];			// �J���������p�����[�^
	float				dist_param[5];			// �c�݃p�����[�^
	e_MBP_Obstacle		obstacle;				// ��Q���̎�ށ@MBP_OBSTACLE_BOX:���AMBP_OBSTACLE_FLOOR:���AMBP_OBSTACLE_NOTHING:��Q������
	float				floor_plane[4];	        // ���ʂ�\�����ʂ̎��̌W��
												// aX + bY + cZ + d = 0 ��(a,b,c,d)
												// �Ⴆ�΁A�J�����ɐ��΂�500mm�̋����ɂ��鏰�ʂ�(a,b,c,d) = (0,0,-1,500)
	float               max_height_from_floor;  // ���ʂ���o���ς݂̕��̂̒��_�܂ł̍��� [mm]
	float				box_width;				// �R���e�i�̕�  (�J�������W�n��X��) [mm]
	float				box_depth;				// �R���e�i�̉��s(�J�������W�n��Y��) [mm]
	float				box_height;				// �R���e�i�̍���(�J�������W�n��Z��) [mm]
	float				box_thickness;			// �R���e�i�̕��̌��� [mm]
	float				box_bottom_height;		// �R���e�i�̒�ʂ̌��� [mm]
	float				handeye_rot_angle[3];	// �n���h�A�C�L�����u���[�V�������ʂ̉�]�p�x [deg]
	float				handeye_trans[3];		// �n���h�A�C�L�����u���[�V�������ʂ̕��i�x�N�g�� [mm]
	float				handeye_rot_mat[9];		// �n���h�A�C�L�����u���[�V�������ʂ̉�]�s��
	BOOL				is_fixed_cam;           // �Œ�J���������w�肷��t���O(TRUE: �Œ�J�����AFALSE: �n���h���ڃJ����)
} MBP_Setting;

typedef struct tagMBPSearchResult
{
	INT32				result_num;				// ���o���ʌ�
	INT32				*object_id;				// ���̂�ID(���[�U�[���o�^���ɐݒ肵�܂�)
	UINT8				*model_id;				// ���f����ID(API���o�^���Ɋ��蓖�Ă܂�)
	float				*score2D;				// ���̗̂֊s�`�󂪃��f���Ƃǂ̒��x��v���邩��\���X�R�A
	float				*score3D;				// ���̂̕\�ʌ`�󂪃��f���Ƃǂ̒��x��v���邩��\���X�R�A
	float				*score_final;			// 2D��3D�̃X�R�A�𓝍������ŏI�X�R�A
	BOOL				*valid_flag;			// ��{�I��TRUE���i�[����܂��B���ʕ`�掞��FALSE��^����ƕ`�悳��܂���B
	float				**pos3D;				// �Z���T���W�n�ɂ�����I�u�W�F�N�g���W���_��3�����ʒu [mm]
	float				**rot3D;				// �Z���T���W�n�ɂ�����I�u�W�F�N�g���W�n�̉�]�p�x
	float				**rot_mat;				// �Z���T���W�n�ɂ�����I�u�W�F�N�g���W�n�̉�]�s��
	float				**obj_cog;				// �Z���T���W�n�ɂ�����I�u�W�F�N�g�d�S�ʒu���W��3�����ʒu [mm]
	INT32				**axis;					// �Z���T���W�n�ɂ�����I�u�W�F�N�g���W�n�̊e����2�����摜�ɓ��e�������W
} MBP_SearchResult;

typedef struct tagMBPGraspResult
{
	// �F�������c���_��
	INT32				result_num;

	// pick_***_tool2cam?���??��?��{?��b?��g?��?��?��?��ɂ͗p?��?��?��܂�?��?��B?��m?��F?��p?��̏o?��͂ł�?��B
	// ?��J?��?��?��?��?��?��?��W?��n?��ɂ�?��?��?��?��s?��b?��L?��?��?��O?��ʒu?��ł̃c?��[?��?��?��̈ʒu?��p?��?��?��Ɠ�?��?��?��ł�?��B
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��?��J?��?��?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̕�?��i?��x?��N?��g?��?��
	float				**pick_pos3D_tool2cam;//[mm]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��J?��?��?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��p?��x
	float				**pick_rot3D_tool2cam;//[deg]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��J?��?��?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��s?��?��
	float				**pick_rot_mat_tool2cam;

	// pick_***_tool2base?���??��?��{?��b?��g?��?��?��?��ɂ͗p?��?��?��?��l?��ł�?��B
	// ?��x?��[?��X?��?��?��W?��n?��ɂ�?��?��?��?��s?��b?��L?��?��?��O?��ʒu?��ł̃c?��[?��?��?��̈ʒu?��p?��?��?��Ɠ�?��?��?��ł�?��B
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̕�?��i?��x?��N?��g?��?��
	float				**pick_pos3D_tool2base;//[mm]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��p?��x
	float				**pick_rot3D_tool2base;//[deg]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃s?��b?��L?��?��?��O?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��s?��?��
	float				**pick_rot_mat_tool2base;

	// approach_***_tool2base?���??��?��{?��b?��g?��?��?��?��ɂ͗p?��?��?��?��l?��ł�?��B
	// ?��x?��[?��X?��?��?��W?��n?��ɂ�?��?��?��?��A?��v?��?��?��[?��`?��ʒu?��ł̃c?��[?��?��?��̈ʒu?��p?��?��?��Ɠ�?��?��?��ł�?��B
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃A?��v?��?��?��[?��`?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̕�?��i?��x?��N?��g?��?��
	float				**approach_pos3D_tool2base;//[mm]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃A?��v?��?��?��[?��`?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��p?��x
	float				**approach_rot3D_tool2base;//[deg]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̃A?��v?��?��?��[?��`?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��s?��?��
	float				**approach_rot_mat_tool2base;

	// pullout_***_tool2base?���??��?��{?��b?��g?��?��?��?��ɂ͗p?��?��?��?��l?��ł�?��B
	// ?��x?��[?��X?��?��?��W?��n?��ɂ�?��?��?��?��?��?��?��?��?��?��?��?��ʒu?��ł̃c?��[?��?��?��̈ʒu?��p?��?��?��Ɠ�?��?��?��ł�?��B
	// ?��c?��[?��?��?��?��?��W?��n?��ł̈�?��?��?��?��?��?��?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̕�?��i?��x?��N?��g?��?��
	float				**pullout_pos3D_tool2base;//[mm]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̈�?��?��?��?��?��?��?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��p?��x
	float				**pullout_rot3D_tool2base;//[deg]
	// ?��c?��[?��?��?��?��?��W?��n?��ł̈�?��?��?��?��?��?��?��ʒu?��?��x?��[?��X?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��s?��?��
	float				**pullout_rot_mat_tool2base;

	// object2tool?���??��?��{?��b?��g?��?��?��?��ɂ͗p?��?��?��܂�?��?��B?��V?��X?��?��?��?��?��`?��?��ɗp?��?��?��邽?��߂̏o?��͂ł�?��B
	// ?��c?��[?��?��?��?��?��W?��n?��ł̕�?��̂̈ʒu?��p?��?��?��Ɠ�?��?��?��ł�?��B
	// ?��?��?��̍�?��W?��n?��?��c?��[?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̕�?��i?��x?��N?��g?��?��
	float				**pos3D_object2tool;//[mm]
	// ?��?��?��̍�?��W?��n?��?��c?��[?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��p?��x
	float				**rot3D_object2tool;//[deg]
	// ?��?��?��̍�?��W?��n?��?��c?��[?��?��?��?��?��W?��n?��ɕϊ�?��?��?��邽?��߂̉�]?��s?��?��
	float				**rot_mat_object2tool;

	// ?��?��?��̈ʒu?��p?��?��?��F?��?��?��?��?��ʂ̃C?��?��?��f?��b?��N?��X
	INT32				*cad_result_id;
	// ?��c?��?��?��Ɏg?��p?��?��?��?��n?��?��?��h?��̃C?��?��?��f?��b?��N?��X
	INT32				*hand_id;
	// ?��?��w?��n?��?��?��h?��?��?��z?��?��?��n?��?��?��h?��?��?��?��w?��肷?��?��t?��?��?��O
	BOOL				*is_twofinger;

	// ���������� ��w�̂� ����������
	// Step?��t?��@?��C?��?��?��̃C?��?��?��f?��b?��N?��X
	INT32				*step_id;
	// ?��c?��?��?��J?��n?��?��?��̃n?��?��?��h?��̊J?��?��?��?��
	INT32				*stroke_start;//[mm]
	// ?��c?��?��?��I?��?��?��?��?��̃n?��?��?��h?��̊J?��?��?��?��
	INT32				*stroke_stop;//[mm]
	// ?��?��a?��c?��?��?��?��?��O?��a?��c?��?��?��?��?��?��w?��肷?��?��t?��?��?��O
	BOOL				*is_close;

	// ?��?��?��?��?��?��?��?��?��?�� ?��z?��?��?��̂� ?��?��?��?��?��?��?��?��?��?��
	// ?��z?��?��?��I?��?��?��?��?��̎֕�?��?��?��̎�?��k?��?��
	float				*shrink_length;//[mm]
} MBP_GraspResult;

// *************************************
//         ?��֐�?��v?��?��?��g?��^?��C?��v?��錾         
// *************************************
	MBP_API MBP_ERR_CODE MBP_AllocSetting(MBP_Setting **setting);
	MBP_API MBP_ERR_CODE MBP_DeleteSetting(MBP_Setting **setting);

	MBP_API MBP_ERR_CODE MBP_AllocSearchResult(MBP_SearchResult **search_result);
	MBP_API MBP_ERR_CODE MBP_DeleteSearchResult(MBP_SearchResult **search_result);

	MBP_API MBP_ERR_CODE MBP_AllocGraspResult(MBP_GraspResult **grasp_result);
	MBP_API MBP_ERR_CODE MBP_DeleteGraspResult(MBP_GraspResult **grasp_result);

	MBP_API MBP_ERR_CODE MBP_AllocMesh(MBP_Mesh **mbp_mesh);
	MBP_API MBP_ERR_CODE MBP_DeleteMesh(MBP_Mesh **mbp_mesh);
	MBP_API MBP_ERR_CODE MBP_AllocMeshes(MBP_Meshes **mbp_meshes);
	MBP_API MBP_ERR_CODE MBP_DeleteMeshes(const INT32 index, MBP_Meshes **mbp_meshes);
	MBP_API MBP_ERR_CODE MBP_DeleteAllMeshes(MBP_Meshes **mbp_meshes);
	MBP_API MBP_ERR_CODE MBP_ReadSTL(const char *cad_filename, MBP_Mesh *mbp_mesh);
	MBP_API MBP_ERR_CODE MBP_ReadSTL2Meshes(const char *cad_filename, const INT32 index, MBP_Meshes *mbp_meshes);

	MBP_API MBP_ERR_CODE MBP_AllocBox(MBP_Box **mbp_box);
	MBP_API MBP_ERR_CODE MBP_DeleteBox(MBP_Box **mbp_box);

	MBP_API MBP_ERR_CODE MBP_TransformSearchResultToBaseCooSys(const MBP_SearchResult *result_cam, const MBP_Setting *setting, const float rot_tool_capture2base[9], const float trans_tool_capture2base[3], MBP_SearchResult *result_base);
	MBP_API MBP_ERR_CODE MBP_ConvertAngleOrder(const float *input_angle, const e_MBP_RotAngleOrder input_order, const INT32 sample_num, float *output_angle, const e_MBP_RotAngleOrder output_order);
	MBP_API char *MBP_GetErrorMessage(const MBP_ERR_CODE error_code);

	MBP_API MBP_ERR_CODE MBP_GetSearchResultSize(const MBP_SearchResult *search_result, INT32 *search_result_size);
	MBP_API MBP_ERR_CODE MBP_CopySearchResult(const MBP_SearchResult *search_result, const INT32 search_result_size, UINT8 *pack_search_result);

#if defined( __cplusplus )
}
#endif


#endif	/* MBP_API_H_ */
