// *********************************************************************
//              (C) Copyright OMRON CORPORATION 2017
//                        All Rights Reserved
// ---------------------------------------------------------------------
//               MBP (Mogra for Bin Picking) �v���W�F�N�g
// *********************************************************************
// �t �@ �C �� �� : mbp_error.h
// ��  ��  �T  �v : �}�N����`�i�G���[�R�[�h�j
// 
// ���t         �쐬��          ���e
// ------------ --------------- ---------------------------------------
// 2017/12/28   Y. Nishina      �V�K�쐬
// *********************************************************************

#ifndef MBP_ERROR_H_
#define MBP_ERROR_H_
//#include "basetsd.h"
#include "win_type.h"

// *************************************
//         �^      ��      �`         
// *************************************
typedef INT32 MBP_ERR_CODE;

// *************************************
//         �}  �N  ��   ��   �`         
// *************************************
#define MAKE_ERROR_CODE(major,minor)		(((major) << 16) | (minor))			// �G���[�R�[�h(32bit)����

// �G���[�R�[�h�ڍ�
#define MBP_MAJOR_NORMAL					0x0000			// Major�F����I��

#define MBP_ERR_MAJOR_VARIOUS				0x0001			// Major�F����`�G���[

#define MBP_ERR_MAJOR_PARAM					0x0002			// Major�F�p�����[�^�G���[
#define MBP_ERR_MINOR_NOT_INITIALIZED		0x0001			// Minor�F��������
#define MBP_ERR_MINOR_INVALID_VALUE			0x0002			// Minor�F�s���Ȓl
#define MBP_ERR_MINOR_NULL					0x0003			// Minor�FNULL
#define MBP_ERR_MINOR_ALREADY_SET			0x0004			// Minor�F�ݒ��

#define MBP_ERR_MAJOR_FILE					0x0003			// Major�F�t�@�C���G���[
#define MBP_ERR_MINOR_CANNOT_OPEN			0x0001			// Minor�F�t�@�C�����J���Ȃ�
#define MBP_ERR_MINOR_INVALID_FORMAT		0x0002			// Minor�F�t�H�[�}�b�g���s��

#define MBP_ERR_MAJOR_MATH					0x0004			// Major�F���w�G���[
#define MBP_ERR_MINOR_ZERO_DIVISION			0x0001			// Minor�F�[����
#define MBP_ERR_MINOR_LOG_NON_POSITIVE		0x0002			// Minor�F�񐳒l�̑ΐ����O
#define MBP_ERR_MINOR_NO_SOLUTION			0x0003			// Minor�F���Ȃ�

#define MBP_ERR_MAJOR_MEMORY				0x0005			// Major�F�������G���[
#define MBP_ERR_MINOR_ALLOC					0x0001			// Minor�F�̈�m�ۃG���[
#define MBP_ERR_MINOR_ZERO_ALLOC			0x0002			// Minor�F�̈�T�C�Y�[���Ń������m��

#define MBP_ERR_MAJOR_IMAGE					0x0006			// Major�F�摜�G���[
#define MBP_ERR_MINOR_OUTSIDE_ACCESS		0x0001			// Minor�F�̈�O�A�N�Z�X

#define MBP_ERR_MAJOR_CAD	    			0x0010			// Major�FCad matching�Ɋւ���G���[
#define MBP_ERR_MAJOR_GRASP	    			0x0011			// Major�FGrasp planning�Ɋւ���G���[
#define MBP_ERR_MAJOR_AOS	    			0x0012			// Major�FActive one shot�Ɋւ���G���[
#define MBP_ERR_MAJOR_HANDEYE    			0x0013			// Major�FHand eye calibration�Ɋւ���G���[
#define MBP_ERR_MAJOR_ENV					0x0014			// Major�FEnvSetup�Ɋւ���G���[
#define MBP_ERR_MAJOR_MV					0x0015			// Major�FMultiView�Ɋւ���G���[
#define MBP_ERR_MAJOR_MODELLESS				0x0016			// Major�FModelLess�Ɋւ���G���[

// �G���[�R�[�h�i32bit�j�� Major code(���16bit) �{ Minor code(����16bit)
#define MBP_NORMAL							MAKE_ERROR_CODE(MBP_MAJOR_NORMAL, 0x0000)

#define MBP_ERR_VARIOUS						MAKE_ERROR_CODE(MBP_ERR_MAJOR_VARIOUS, 0x0000)

#define MBP_ERR_PARAM_NOT_INITIALIZED		MAKE_ERROR_CODE(MBP_ERR_MAJOR_PARAM, MBP_ERR_MINOR_NOT_INITIALIZED)
#define MBP_ERR_PARAM_INVALID_VALUE			MAKE_ERROR_CODE(MBP_ERR_MAJOR_PARAM, MBP_ERR_MINOR_INVALID_VALUE)
#define MBP_ERR_PARAM_NULL					MAKE_ERROR_CODE(MBP_ERR_MAJOR_PARAM, MBP_ERR_MINOR_NULL)
#define MBP_ERR_PARAM_ALREADY_SET			MAKE_ERROR_CODE(MBP_ERR_MAJOR_PARAM, MBP_ERR_MINOR_ALREADY_SET)

#define MBP_ERR_FILE_CANNOT_OPEN			MAKE_ERROR_CODE(MBP_ERR_MAJOR_FILE, MBP_ERR_MINOR_CANNOT_OPEN)
#define MBP_ERR_FILE_INVALID_FORMAT			MAKE_ERROR_CODE(MBP_ERR_MAJOR_FILE, MBP_ERR_MINOR_INVALID_FORMAT)

#define MBP_ERR_MATH_ZERO_DIVIZION			MAKE_ERROR_CODE(MBP_ERR_MAJOR_MATH, MBP_ERR_MINOR_ZERO_DIVISION)
#define MBP_ERR_MATH_LOG_NON_POSITIVE		MAKE_ERROR_CODE(MBP_ERR_MAJOR_MATH, MBP_ERR_MINOR_LOG_NON_POSITIVE)
#define MBP_ERR_MATH_NO_SOLUTION			MAKE_ERROR_CODE(MBP_ERR_MAJOR_MATH, MBP_ERR_MINOR_NO_SOLUTION)

#define MBP_ERR_MEMORY_ALLOC				MAKE_ERROR_CODE(MBP_ERR_MAJOR_MEMORY, MBP_ERR_MINOR_ALLOC)
#define MBP_ERR_MEMORY_ZERO_ALLOC			MAKE_ERROR_CODE(MBP_ERR_MAJOR_MEMORY, MBP_ERR_MINOR_ZERO_ALLOC)

#define MBP_ERR_IMAGE_OUTSIDE_ACCESS		MAKE_ERROR_CODE(MBP_ERR_MAJOR_IMAGE, MBP_ERR_MINOR_OUTSIDE_ACCESS)

#define GET_ERROR_MAJOR(e)				    (((e) & 0x0FFFF0000) >> 16)			// Major�R�[�h�擾
#define GET_ERROR_HIGH_MINOR(e)			    (((e) >> 8) & 0x000000FF)			// Minor�R�[�h�E���8bit�擾
#define GET_ERROR_LOW_MINOR(e)			    ((e) & 0x000000FF)					// Minor�R�[�h�E����8bit�擾


#endif	/* MBP_ERROR_H_ */