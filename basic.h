#pragma once

#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <random>

#include "HandModel.h"
#include "CameraInfo.h"

#define depth_height 480
#define depth_width 640
#define depth_MSRA_height 240
#define depth_MSRA_width 320


#define Global
#define MaxBatch 512
#define INF 1e30
#define eps 1e-6 // c++ precision is that accurate enough (unlike PASCAL LOL)
#define Display_Edge_In_Image
#define depth_lb 250
#define depth_ub 850
#define depth_MSRA_lb 150 //0.5 ft https://software.intel.com/sites/default/files/article/401008/creativelabs-camera-productbrief-final.pdf Intel Interactive Gesture Camera
#define depth_MSRA_ub 990 //3.25 ft
#define PI 3.1415926535897932384626433832795
#define maxlen 555
#define maxnum 555


//display settings
// + b1) * mul1 + b2) * mul2 + b3
const double b1[2] = { 0, 0 };
const double mul1[2] = { 1.0, 1.0 };
const double b2[2] = { 0.0, 0.0 };
const double mul2[2] = { 1.0, 1.0 };
const double b3[2] = { 0.0, 0.0 };


//NYU 30 bone pred
const int color_pred_bone_NYU[BoneNum_NYU][3] =
{
	//little finger
	{ 0, 0, 255 },    //0  little_finger_tip -> little_finger_dip
	{ 0, 0, 255 },    //1  little_finger_dip -> little_finger_pip_second
	{ 0, 0, 255 },    //2  little_finger_pip_second -> little_finger_pip_first 
	{ 0, 0, 255 },    //3  little_finger_pip_first -> little_finger_base
	{ 0, 0, 255 },    //4  little_finger_base -> little_finger_mcp
	{ 0, 0, 255 },    //5  little_finger_mcp -> palm_center

	//ring finger
	{ 0, 255, 255 },  //6  ring_finger_tip -> ring_finger_dip
	{ 0, 255, 255 },  //7  ring_finger_dip -> ring_finger_pip_second
	{ 0, 255, 255 },  //8  ring_finger_pip_second -> ring_finger_pip_first 
	{ 0, 255, 255 },  //9  ring_finger_pip_first -> ring_finger_base
	{ 0, 255, 255 },  //10 ring_finger_base -> ring_finger_mcp
	{ 0, 255, 255 },  //11 ring_finger_mcp -> palm_center

	//middle finger
	{ 0, 255, 0 },    //12 middle_finger_tip -> middle_finger_dip
	{ 0, 255, 0 },    //13 middle_finger_dip -> middle_finger_pip_second
	{ 0, 255, 0 },    //14 middle_finger_pip_second -> middle_finger_pip_first 
	{ 0, 255, 0 },    //15 middle_finger_pip_first -> middle_finger_base
	{ 0, 255, 0 },    //16 middle_finger_base -> middle_finger_mcp
	{ 0, 255, 0 },    //17 middle_finger_mcp -> palm_center

	//index finger
	{ 255, 0, 0 },    //18 index_finger_tip -> index_finger_dip
	{ 255, 0, 0 },    //19 index_finger_dip -> index_finger_pip_second
	{ 255, 0, 0 },    //20 index_finger_pip_second -> index_finger_pip_first 
	{ 255, 0, 0 },    //21 index_finger_pip_first -> index_finger_base
	{ 255, 0, 0 },    //22 index_finger_base -> index_finger_mcp
	{ 255, 0, 0 },    //23 index_finger_mcp -> palm_center

	//wrist
	{ 255, 0, 255 },  //24 palm_center -> wrist_left
	{ 255, 0, 255 },  //25 palm_center -> wrist_middle

	//thumb
	{ 255, 0, 255 },  //26 palm_center -> thumb_finger_mcp
	{ 255, 0, 255 },  //27 thumb_finger_mcp -> thumb_finger_pip
	{ 255, 0, 255 },  //28 thumb_finger_pip -> thumb_finger_dip
	{ 255, 0, 255 },  //29 thumb_finger_dip -> thumb_finger_tip

};

const int color_pred_bone_MSRA[BoneNum_MSRA][3] =
{
	//index finger
	{ 42, 120, 37 },    //0  imcp -> wrist
	{ 42, 120, 37 },    //1  ipip -> imcp
	{ 42, 120, 37 },    //2  idip -> ipip
	{ 42, 120, 37 },    //3  itip -> idip	

	//middle finger
	{ 246, 0, 0 },       //4  mmcp -> wrist
	{ 246, 0, 0 },      //5  mpip -> mmcp
	{ 246, 0, 0 },      //6  mdip -> mpip
	{ 246, 0, 0 },      //7  mtip -> mdip	

	//ring finger
	{ 250, 0, 235 },    //8  rmcp -> wrist
	{ 250, 0, 235 },    //9  rpip -> rmcp
	{ 250, 0, 235 },    //10 rdip -> rpip
	{ 250, 0, 235 },    //11 rtip -> rdip

	//pinky finger	
	{ 0, 255, 255 },    //12 pmcp -> wrist
	{ 0, 255, 255 },    //13 ppip -> pmcp
	{ 0, 255, 255 },    //14 pdip -> ppip
	{ 0, 255, 255 },    //15 ptip -> pdip	

	//thumb finger
	{ 0, 0, 255 },      //16 tmcp -> wrist
	{ 0, 0, 255 },      //17 tpip -> tmcp
	{ 0, 0, 255 },      //19 tdip -> tpip
	{ 0, 0, 255 },      //20 ttip -> tdip
};


const int color_pred_bone_ICVL[BoneNum_ICVL][3] =
{
	//pinky finger
	{ 0, 0, 255 },    //0  pinky_tip -> pinky_pip
	{ 0, 0, 255 },    //1  pinky_pip -> pinky_mcp
	{ 0, 0, 255 },    //2  pinky_mcp -> palm_center 

	//ring finger
	{ 0, 255, 255 },  //3  ring_tip -> ring_pip
	{ 0, 255, 255 },  //4  ring_pip -> ring_mcp
	{ 0, 255, 255 },  //5  ring_mcp -> palm_center

	//middle finger
	{ 0, 255, 0 },    //6 middle_tip -> middle_pip
	{ 0, 255, 0 },    //7 middle_pip -> middle_mcp
	{ 0, 255, 0 },    //8 middle_mcp -> palm_center

	//index finger
	{ 255, 0, 0 },    //9 index_tip -> index_pip
	{ 255, 0, 0 },    //10 index_pip -> index_mcp
	{ 255, 0, 0 },    //11 index_mcp -> palm_center

	//thumb
	{ 255, 0, 255 },  //12 thumb_mcp -> palm_center
	{ 255, 0, 255 },  //13 thumb_dip -> thumb_mcp
	{ 255, 0, 255 },  //14 thumb_tip -> thumb_dip

};


//NYU 13 bone pred
const int color_pred_bone_NYU_Eval[BoneNum_NYU_Eval][3] =
{
	//little finger
	{ 0, 0, 255 },    //0  little_finger_tip -> little_finger_pip_first


	{ 0, 0, 255 },    //3  little_finger_pip_first -> palm_center



	//ring finger
	{ 0, 255, 255 },  //6  ring_finger_tip -> ring_finger_pip_first


	{ 0, 255, 255 },  //9  ring_finger_pip_first -> palm_center



	//middle finger
	{ 0, 255, 0 },    //12 middle_finger_tip -> middle_finger_pip_first


	{ 0, 255, 0 },    //15 middle_finger_pip_first -> palm_center



	//index finger
	{ 255, 0, 0 },    //18 index_finger_tip -> index_finger_pip_first


	{ 255, 0, 0 },    //21 index_finger_pip_first -> palm_center



	//wrist
	{ 255, 0, 255 },  //24 palm_center -> wrist_left
	{ 255, 0, 255 },  //25 palm_center -> wrist_middle

	//thumb
	{ 255, 0, 255 },  //26 palm_center -> thumb_finger_pip

	{ 255, 0, 255 },  //28 thumb_finger_pip -> thumb_finger_dip
	{ 255, 0, 255 },  //29 thumb_finger_dip -> thumb_finger_tip

};

const int color_pred_bone[BoneNum][3] = {
	{ 255, 0, 255 },  //ttip -> tdip
	{ 255, 0, 255 },  //tdip -> tpip
	{ 255, 0, 255 },  //tpip -> tmcp
	{ 255, 0, 255 },  //tmcp -> wrist

	{ 255, 0, 0 },  //itip -> idip
	{ 255, 0, 0 },   //idip -> ipip
	{ 255, 0, 0 },  //ipip -> imcp
	{ 255, 0, 0 },  //imcp -> wrist

	{ 0, 255, 0 },     //mtip -> mdip
	{ 0, 255, 0 },     //mdip -> mpip
	{ 0, 255, 0 },     //mpip -> mmcp
	{ 0, 255, 0 },     //mmcp -> wrist

	{ 0, 255, 255 },   //rtip -> rdip 
	{ 0, 255, 255 },   //rdip -> rpip
	{ 0, 255, 255 },   //rpip -> rmcp
	{ 0, 255, 255 },   //rmcp -> wrist

	{ 0, 0, 255 },     //ptip -> pdip 
	{ 0, 0, 255 },     //pdip -> ppip
	{ 0, 0, 255 },     //ppip -> pmcp
	{ 0, 0, 255 },     //pmcp -> wrist
};

//NYU 31 joints pred
const int color_pred_joint_NYU[JointNum_NYU][3] =
{
	//little finger
	{ 0, 0, 255 },    //0  little_finger_tip
	{ 0, 0, 255 },    //1  little_finger_dip
	{ 0, 0, 255 },    //2  little_finger_pip_second
	{ 0, 0, 255 },    //3  little_finger_pip_first
	{ 0, 0, 255 },    //4  little_finger_base

	//ring finger
	{ 0, 255, 255 },  //5  ring_finger_tip
	{ 0, 255, 255 },  //6  ring_finger_dip
	{ 0, 255, 255 },  //7  ring_finger_pip_second
	{ 0, 255, 255 },  //8  ring_finger_pip_first
	{ 0, 255, 255 },  //9  ring_finger_base

	//middle finger
	{ 0, 255, 0 },    //10 middle_finger_tip
	{ 0, 255, 0 },    //11 middle_finger_dip
	{ 0, 255, 0 },    //12 middle_finger_pip_second
	{ 0, 255, 0 },    //13 middle_finger_pip_first
	{ 0, 255, 0 },    //14 middle_finger_base

	//index finger
	{ 255, 0, 0 },    //15 index_finger_tip
	{ 255, 0, 0 },    //16 index_finger_dip
	{ 255, 0, 0 },    //17 index_finger_pip_second
	{ 255, 0, 0 },    //18 index_finger_pip_first
	{ 255, 0, 0 },    //19 index_finger_base

	//MCP
	{ 0, 0, 255 },    //20 little_finger_MCP
	{ 0, 255, 255 },  //21 ring_finger_MCP
	{ 0, 255, 0 },    //22 middle_finger_MCP
	{ 255, 0, 0 },    //23 index_finger_MCP

	//palm center
	{ 0, 0, 0 },      //24 palm_center

	//wrist left wrist middle
	{ 255, 0, 255 },  //25 wrist_left
	{ 255, 0, 255 },  //26 wrist_middle

	//thumb finger
	{ 255, 0, 255 },  //27 thumb_finger_MCP
	{ 255, 0, 255 },  //28 thumb_finger_pip
	{ 255, 0, 255 },  //29 thumb_finger_dip
	{ 255, 0, 255 },  //30 thumb_finger_tip

};

//NYU 14 joints pred
const int color_pred_joint_NYU_Eval[JointNum_NYU_Eval][3] =
{
	//little finger
	{ 0, 0, 255 },    //0  little_finger_tip


	{ 0, 0, 255 },    //3  little_finger_pip_first


	//ring finger
	{ 0, 255, 255 },  //5  ring_finger_tip


	{ 0, 255, 255 },  //8  ring_finger_pip_first


	//middle finger
	{ 0, 255, 0 },    //10 middle_finger_tip


	{ 0, 255, 0 },    //13 middle_finger_pip_first


	//index finger
	{ 255, 0, 0 },    //15 index_finger_tip


	{ 255, 0, 0 },    //18 index_finger_pip_first

	//palm center
	{ 0, 0, 0 },      //24 palm_center

	//wrist left wrist middle
	{ 255, 0, 255 },  //25 wrist_left
	{ 255, 0, 255 },  //26 wrist_middle

	//thumb finger
	{ 255, 0, 255 },  //28 thumb_finger_pip
	{ 255, 0, 255 },  //29 thumb_finger_dip
	{ 255, 0, 255 },  //30 thumb_finger_tip


};

const int color_pred_joint_MSRA[JointNum_MSRA][3] =
{
	//wrist
	{ 255, 255, 255 },  //0 wrist

	//index finger
	{ 42, 120, 37 },    //1  imcp
	{ 42, 120, 37 },    //2  ipip
	{ 42, 120, 37 },    //3  idip
	{ 42, 120, 37 },    //4  itip

	//middle finger
	{ 246, 0, 0 },      //5  mmcp 
	{ 246, 0, 0 },      //6  mpip 
	{ 246, 0, 0 },      //7  mdip 
	{ 246, 0, 0 },      //8  mtip 

	//ring finger
	{ 250, 0, 235 },    //9  rmcp 
	{ 250, 0, 235 },    //10 rpip 
	{ 250, 0, 235 },    //11 rdip 
	{ 250, 0, 235 },    //12 rtip 

	//pinky finger	
	{ 0, 255, 255 },    //13 pmcp 
	{ 0, 255, 255 },    //14 ppip 
	{ 0, 255, 255 },    //15 pdip 
	{ 0, 255, 255 },    //16 ptip 

	//thumb finger
	{ 0, 0, 255 },      //17 tmcp -> wrist
	{ 0, 0, 255 },      //18 tpip -> tmcp
	{ 0, 0, 255 },      //19 tdip -> tpip
	{ 0, 0, 255 },      //20 ttip -> tdip
};


//ICVL 16 joints pred
const int color_pred_joint_ICVL[JointNum_ICVL][3] =
{
	//palm center
	{ 0, 0, 0 },      //0  palm_center

	//thumb finger
	{ 255, 0, 255 },  //1  thumb_mcp
	{ 255, 0, 255 },  //2  thumb_dip
	{ 255, 0, 255 },  //3  thumb_tip

	//index finger
	{ 255, 0, 0 },    //4  index_mcp
	{ 255, 0, 0 },    //5  index_pip
	{ 255, 0, 0 },    //6  index_tip

	//middle finger
	{ 0, 255, 0 },    //7  middle_mcp
	{ 0, 255, 0 },    //8  middle_pip
	{ 0, 255, 0 },    //9  middle_tip

	//ring finger
	{ 0, 255, 255 },  //10 ring_mcp
	{ 0, 255, 255 },  //11 ring_pip
	{ 0, 255, 255 },  //12 ring_tip

	//little finger
	{ 0, 0, 255 },    //13 pinky_mcp
	{ 0, 0, 255 },    //14 pinky_pip
	{ 0, 0, 255 },    //15 pinky_tip

};

const int color_pred_joint[JointNum][3] =
{
	{ 0, 0, 0 },        //wrist
	{ 255, 0, 255 },    //tmcp
	{ 255, 0, 0 },      //imcp
	{ 0, 255, 0 },      //mmcp
	{ 0, 255, 255 },    //rmcp
	{ 0, 0, 255 },      //pmcp

	{ 255, 0, 255 },    //tpip
	{ 255, 0, 255 },    //tdip
	{ 255, 0, 255 },    //ttip

	{ 255, 0, 0 },      //ipip
	{ 255, 0, 0 },      //idip
	{ 255, 0, 0 },      //itip

	{ 0, 255, 0 },      //mpip
	{ 0, 255, 0 },      //mdip
	{ 0, 255, 0 },      //mtip

	{ 0, 255, 255 },    //rpip
	{ 0, 255, 255 },    //rdip
	{ 0, 255, 255 },    //rtip

	{ 0, 0, 255 },      //ppip	
	{ 0, 0, 255 },      //pdip	
	{ 0, 0, 255 },      //ptip
};

//NYU 31 joints GT
const int color_gt_joint_NYU[JointNum_NYU][3] =
{
	//little finger
	{ 39, 127, 255 },    //0  little_finger_tip
	{ 39, 127, 255 },    //1  little_finger_dip
	{ 39, 127, 255 },    //2  little_finger_pip_second
	{ 39, 127, 255 },    //3  little_finger_pip_first
	{ 39, 127, 255 },    //4  little_finger_base

	//ring finger
	{ 39, 127, 255 },    //5  ring_finger_tip
	{ 39, 127, 255 },    //6  ring_finger_dip
	{ 39, 127, 255 },    //7  ring_finger_pip_second
	{ 39, 127, 255 },    //8  ring_finger_pip_first
	{ 39, 127, 255 },    //9  ring_finger_base

	//middle finger
	{ 39, 127, 255 },    //10 middle_finger_tip
	{ 39, 127, 255 },    //11 middle_finger_dip
	{ 39, 127, 255 },    //12 middle_finger_pip_second
	{ 39, 127, 255 },    //13 middle_finger_pip_first
	{ 39, 127, 255 },    //14 middle_finger_base

	//index finger
	{ 39, 127, 255 },    //15 index_finger_tip
	{ 39, 127, 255 },    //16 index_finger_dip
	{ 39, 127, 255 },    //17 index_finger_pip_second
	{ 39, 127, 255 },    //18 index_finger_pip_first
	{ 39, 127, 255 },    //19 index_finger_base

	//MCP
	{ 39, 127, 255 },    //20 little_finger_MCP
	{ 39, 127, 255 },    //21 ring_finger_MCP
	{ 39, 127, 255 },    //22 middle_finger_MCP
	{ 39, 127, 255 },    //23 index_finger_MCP

	//palm center
	{ 39, 127, 255 },    //24 palm center

	//wrist left wrist middle
	{ 39, 127, 255 },    //25 wrist_left 
	{ 39, 127, 255 },    //26 wrist_middle

	//thumb finger
	{ 39, 127, 255 },    //27 thumb_finger_mcp
	{ 39, 127, 255 },    //28 thumb_finger_pip
	{ 39, 127, 255 },    //29 thumb_finger_dip
	{ 39, 127, 255 },    //30 thumb_finger_tip


};

//NYU 14 joints GT
const int color_gt_joint_NYU_Eval[JointNum_NYU_Eval][3] =
{
	//little finger
	{ 39, 127, 255 },    //0  little_finger_tip


	{ 39, 127, 255 },    //3  little_finger_pip_first


	//ring finger
	{ 39, 127, 255 },    //5  ring_finger_tip


	{ 39, 127, 255 },    //8  ring_finger_pip_first


	//middle finger
	{ 39, 127, 255 },    //10 middle_finger_tip


	{ 39, 127, 255 },    //13 middle_finger_pip_first


	//index finger
	{ 39, 127, 255 },    //15 index_finger_tip


	{ 39, 127, 255 },    //18 index_finger_pip_first

	//palm center
	{ 39, 127, 255 },    //24 palm_center

	//wrist left wrist middle
	{ 39, 127, 255 },    //25 wrist_left
	{ 39, 127, 255 },    //26 wrist_middle

	//thumb finger
	{ 39, 127, 255 },    //28 thumb_finger_pip
	{ 39, 127, 255 },    //29 thumb_finger_dip
	{ 39, 127, 255 },    //30 thumb_finger_tip

};

const int color_gt_joint_MSRA[JointNum_MSRA][3] =
{
	{ 39, 127, 255 },    //wrist_MSRA

	//index finger
	{ 39, 127, 255 },    //imcp_MSRA
	{ 39, 127, 255 },    //ipip_MSRA
	{ 39, 127, 255 },    //idip_MSRA
	{ 39, 127, 255 },    //itip_MSRA	

	//middle finger
	{ 39, 127, 255 },    //mmcp_MSRA
	{ 39, 127, 255 },    //mpip_MSRA
	{ 39, 127, 255 },    //mdip_MSRA
	{ 39, 127, 255 },    //mtip_MSRA

	//ring finger
	{ 39, 127, 255 },    //rmcp_MSRA
	{ 39, 127, 255 },    //rpip_MSRA
	{ 39, 127, 255 },    //rdip_MSRA
	{ 39, 127, 255 },    //rtip_MSRA

	//pinky finger
	{ 39, 127, 255 },    //pmcp_MSRA
	{ 39, 127, 255 },    //ppip_MSRA
	{ 39, 127, 255 },    //pdip_MSRA
	{ 39, 127, 255 },    //ptip_MSRA

	//thumb finger
	{ 39, 127, 255 },    //tmcp_MSRA
	{ 39, 127, 255 },    //tpip_MSRA
	{ 39, 127, 255 },    //tdip_MSRA
	{ 39, 127, 255 },    //ttip_MSRA

};


//ICVL 16 joints gt
const int color_gt_joint_ICVL[JointNum_ICVL][3] =
{
	//palm center
	{ 39, 127, 255 },      //0  palm_center

	//thumb finger
	{ 39, 127, 255 },   //1  thumb_mcp
	{ 39, 127, 2555 },  //2  thumb_dip
	{ 39, 127, 255 },   //3  thumb_tip

	//index finger
	{ 39, 127, 255 },   //4  index_mcp
	{ 39, 127, 255 },   //5  index_pip
	{ 39, 127, 255 },   //6  index_tip

	//middle finger
	{ 39, 127, 2550 },  //7  middle_mcp
	{ 39, 127, 255 },   //8  middle_pip
	{ 39, 127, 255 },   //9  middle_tip

	//ring finger
	{ 39, 127, 255 },   //10 ring_mcp
	{ 39, 127, 255 },   //11 ring_pip
	{ 39, 127, 255 },   //12 ring_tip

	//little finger
	{ 39, 127, 255 },   //13 pinky_mcp
	{ 39, 127, 2555 },  //14 pinky_pip
	{ 39, 127, 255 },   //15 pinky_tip
	 
};

const int color_gt_joint[JointNum][3] =
{
	{ 39, 127, 255 },    //wrist
	{ 39, 127, 255 },    //tmcp
	{ 39, 127, 255 },    //imcp
	{ 39, 127, 255 },    //mmcp
	{ 39, 127, 255 },    //rmcp
	{ 39, 127, 255 },    //pmcp

	{ 39, 127, 255 },    //tpip
	{ 39, 127, 255 },    //tdip
	{ 39, 127, 255 },    //ttip

	{ 39, 127, 255 },      //ipip
	{ 39, 127, 255 },      //idip
	{ 39, 127, 255 },      //itip

	{ 39, 127, 255 },      //mpip
	{ 39, 127, 255 },      //mdip
	{ 39, 127, 255 },      //mtip

	{ 39, 127, 255 },    //rpip
	{ 39, 127, 255 },    //rdip
	{ 39, 127, 255 },    //rtip

	{ 39, 127, 255 },      //ppip	
	{ 39, 127, 255 },      //pdip	
	{ 39, 127, 255 },      //ptip
};

//NYU 30 bone GT
const int color_gt_bone_NYU[BoneNum_NYU][3] = {
	//little finger
	{ 39, 127, 255 },    //0  little_finger_tip -> little_finger_dip
	{ 39, 127, 255 },    //1  little_finger_dip -> little_finger_pip_second
	{ 39, 127, 255 },    //2  little_finger_pip_second -> little_finger_pip_first
	{ 39, 127, 255 },    //3  little_finger_pip_first -> little_finger_base
	{ 39, 127, 255 },    //4  little_finger_base -> little_finger_mcp
	{ 39, 127, 255 },    //5  little_finger_mcp -> palm center

	//ring finger
	{ 39, 127, 255 },    //6  ring_finger_tip -> ring_finger_dip
	{ 39, 127, 255 },    //7  ring_finger_dip -> ring_finger_pip_second
	{ 39, 127, 255 },    //8  ring_finger_pip_second -> ring_finger_pip_first
	{ 39, 127, 255 },    //9  ring_finger_pip_first -> ring_finger_base
	{ 39, 127, 255 },    //10 ring_finger_base -> ring_finger_mcp
	{ 39, 127, 255 },    //11 ring_finger_mcp -> palm_center

	//middle finger
	{ 39, 127, 255 },    //12 middle_finger_tip -> middle_finger_dip
	{ 39, 127, 255 },    //13 middle_finger_dip -> middle_finger_pip_second
	{ 39, 127, 255 },    //14 middle_finger_pip_second -> middle_finger_pip_first
	{ 39, 127, 255 },    //15 middle_finger_pip_first -> middle_finger_base
	{ 39, 127, 255 },    //16 middle_finger_base -> middle_finger_mcp
	{ 39, 127, 255 },    //17 middle_finger_mcp -> palm_center

	//index finger
	{ 39, 127, 255 },    //18 index_finger_tip -> index_finger_dip
	{ 39, 127, 255 },    //19 index_finger_dip -> index_finger_pip_second
	{ 39, 127, 255 },    //20 index_finger_pip_second -> index_finger_pip_first
	{ 39, 127, 255 },    //21 index_finger_pip_first -> index_finger_base
	{ 39, 127, 255 },    //22 index_finger_base -> index_finger_mcp
	{ 39, 127, 255 },    //23 index_finger_mcp -> palm_center

	//wrist left middle
	{ 39, 127, 255 },    //24 palm_center -> wrist_left
	{ 39, 127, 255 },    //25 palm_center -> wrist_middle

	//thumb finger
	{ 39, 127, 255 },    //26 palm_center -> thumb_finger_mcp
	{ 39, 127, 255 },    //27 thumb_finger_mcp -> thumb_finger_pip
	{ 39, 127, 255 },    //28 thumb_finger_pip -> thumb_finger_dip
	{ 39, 127, 255 },    //29 thumb_finger_dip -> thumb_finger_tip
};

//NYU 13 bone GT
const int color_gt_bone_NYU_Eval[BoneNum_NYU_Eval][3] = {
	//little finger
	{ 39, 127, 255 },    //0  little_finger_tip -> little_finger_pip_first


	{ 39, 127, 255 },    //3  little_finger_pip_first -> palm_center



	//ring finger
	{ 39, 127, 255 },    //6  ring_finger_tip -> ring_finger_pip_first


	{ 39, 127, 255 },    //9  ring_finger_pip_first -> palm_center



	//middle finger
	{ 39, 127, 255 },    //12 middle_finger_tip -> middle_finger_pip_first


	{ 39, 127, 255 },    //15 middle_finger_pip_first -> palm_center



	//index finger
	{ 39, 127, 255 },    //18 index_finger_tip -> index_finger_pip_first


	{ 39, 127, 255 },    //21 index_finger_pip_first -> palm_center



	//wrist left middle
	{ 39, 127, 255 },    //24 palm_center -> wrist_left
	{ 39, 127, 255 },    //25 palm_center -> wrist_middle

	//thumb finger

	{ 39, 127, 255 },    //27 palm_center -> thumb_finger_pip
	{ 39, 127, 255 },    //28 thumb_finger_pip -> thumb_finger_dip
	{ 39, 127, 255 },    //29 thumb_finger_dip -> thumb_finger_tip
};

const int color_gt_bone_MSRA[BoneNum_MSRA][3] = {
	//index finger
	{ 39, 127, 255 },  //imcp -> wrist
	{ 39, 127, 255 },  //ipip - imcp
	{ 39, 127, 255 },  //idip -> ipip
	{ 39, 127, 255 },  //itip -> idip

	//middle finger
	{ 39, 127, 255 },  //mmcp -> wrist
	{ 39, 127, 255 },  //mpip -> mmcp
	{ 39, 127, 255 },  //mdip -> mpip
	{ 39, 127, 255 },  //mtip -> mdip

	//ring finger
	{ 39, 127, 255 },  //rmcp -> wrist
	{ 39, 127, 255 },  //rpip -> rmcp
	{ 39, 127, 255 },  //rdip -> rpip
	{ 39, 127, 255 },  //rtip -> rdip

	//little(pinky) finger
	{ 39, 127, 255 },  //pmcp -> wrist
	{ 39, 127, 255 },  //ppip -> pmcp
	{ 39, 127, 255 },  //pdip -> ppip
	{ 39, 127, 255 },  //ptip -> pdip
};


const int color_gt_bone_ICVL[BoneNum_ICVL][3] =
{
	//pinky finger
	{ 39, 127, 255 },    //0  pinky_tip -> pinky_pip
	{ 39, 127, 255 },    //1  pinky_pip -> pinky_mcp
	{ 39, 127, 255 },    //2  pinky_mcp -> palm_center 

	//ring finger
	{ 39, 127, 255 },    //3  ring_tip -> ring_pip
	{ 39, 127, 255 },    //4  ring_pip -> ring_mcp
	{ 39, 127, 255 },    //5  ring_mcp -> palm_center

	//middle finger
	{ 39, 127, 255 },    //6 middle_tip -> middle_pip
	{ 39, 127, 255 },    //7 middle_pip -> middle_mcp
	{ 39, 127, 255 },    //8 middle_mcp -> palm_center

	//index finger
	{ 39, 127, 255 },    //9 index_tip -> index_pip
	{ 39, 127, 255 },    //10 index_pip -> index_mcp
	{ 39, 127, 255 },    //11 index_mcp -> palm_center

	//thumb
	{ 39, 127, 255 },    //12 thumb_mcp -> palm_center
	{ 39, 127, 255 },    //13 thumb_dip -> thumb_mcp
	{ 39, 127, 255 },    //14 thumb_tip -> thumb_dip

};

const int color_gt_bone[BoneNum][3] = {
	{ 39, 127, 255 },  //ttip -> tdip
	{ 39, 127, 255 },  //tdip -> tpip
	{ 39, 127, 255 },  //tpip -> tmcp
	{ 39, 127, 255 },  //tmcp -> wrist

	{ 39, 127, 255 },  //itip -> idip
	{ 39, 127, 255 },   //idip -> ipip
	{ 39, 127, 255 },  //ipip -> imcp
	{ 39, 127, 255 },  //imcp -> wrist

	{ 39, 127, 255 },     //mtip -> mdip
	{ 39, 127, 255 },     //mdip -> mpip
	{ 39, 127, 255 },     //mpip -> mmcp
	{ 39, 127, 255 },     //mmcp -> wrist

	{ 39, 127, 255 },   //rtip -> rdip 
	{ 39, 127, 255 },   //rdip -> rpip
	{ 39, 127, 255 },   //rpip -> rmcp
	{ 39, 127, 255 },   //rmcp -> wrist

	{ 39, 127, 255 },     //ptip -> pdip 
	{ 39, 127, 255 },     //pdip -> ppip
	{ 39, 127, 255 },     //ppip -> pmcp
	{ 39, 127, 255 },     //pmcp -> wrist
};


const int skeleton_color_bone_gt_NYU[BoneNum_NYU][3] =
{
	//little finger 
	{ 125, 126, 130 }, //little_finger_tip -> little_finger_dip
	{ 127, 131, 0 },   //little_finger_dip -> little_finger_pip_second
	{ 254, 0, 0 },     //little_finger_pip_second -> little_pip_first
	{ 90, 124, 286 },  //little_finger_pip_first -> little_finger_base
	{ 230, 190, 199 }, //little_finger_base -> little_finger_mcp
	{ 50, 169, 187 },  //little_finger_mcp -> palm_center

	//ring finger
	{ 125, 0, 133 },   //ring_finger_tip -> ring_finger_dip
	{ 0, 127, 123 },   //ring_finger_dip -> ring_finger_pip_second
	{ 2, 255, 1 },     //ring_finger_pip_second -> ring_finger_pip_first
	{ 0, 242, 255 },   //ring_finger_pip_first -> ring_finger_base
	{ 190, 146, 112 }, //ring_finger_base -> ring_finger_mcp
	{ 141, 24, 213 }, //ring_finger_mcp -> palm_center

	//middle finger
	{ 135, 0, 1 },     //middle_finger_tip -> middle_finger_dip
	{ 0, 129, 1 },     //middle_finger_dip -> middle_finger_pip_second
	{ 25, 0, 128 },    //middle_finger_pip_second -> middle_finger_pip_first
	{ 135, 0, 1 },     //middle_finger_pip_first -> middle_finger_base
	{ 233, 216, 152 }, //middle_finger_base -> middle_finger_mcp
	{ 233, 216, 4 },   //middle_finger_mcp -> palm_center

	//index finger
	{ 40, 127, 254 },  //index_finger_tip -> index_finger_dip
	{ 250, 254, 1 },   //index_finger_dip -> index_finger_pip_second
	{ 200, 173, 253 }, //index_finger_pip_second -> index_finger_pip_first
	{ 106, 190, 71 },  //index_finger_pip_first -> index_finger_base
	{ 164, 73, 163 },  //index_finger_base -> index_finger_mcp
	{ 2, 37, 234 },    //index_finger_mcp -> palm_center

	//wrist left wrist middle
	{ 127, 146, 105 }, //palm_center -> wrist_left
	{ 64, 64, 0 },    //palm_center -> wrist_middle

	//thumb
	{ 127, 1, 64 },    //palm_center -> thumb_mcp
	{ 191, 128, 254 }, //thumb_mcp -> thumb_pip
	{ 1, 64, 128 },    //thumb_pip -> thumb_dip
	{ 179, 242, 187 }  //thumb_dip -> thumb_tip

};

const int skeleton_color_bone_gt_NYU_Eval[BoneNum_NYU_Eval][3] =
{
	//little finger 
	{ 126, 125, 132 }, //little_finger_tip -> little_finger_pip_first


	{ 138, 128, 6 },  //little_finger_pip_first -> palm_center



	//ring finger
	{ 130, 13, 128 },   //ring_finger_tip -> ring_finger_pip_first


	{ 6, 132, 122 },   //ring_finger_pip_first -> palm_center



	//middle finger
	{ 123, 10, 8 },     //middle_finger_tip -> middle_finger_pip_first


	{ 38, 145, 35 },     //middle_finger_pip_first -> palm_center



	//index finger
	{ 5, 5, 130 },  //index_finger_tip -> index_finger_pip_first


	{ 235, 255, 51 },  //index_finger_pip_first -> palm_center



	//wrist left wrist middle
	{ 53, 245, 255 },     //palm_center -> wrist_left
	{ 192, 234, 242 },    //palm_center -> wrist_middle
	{ 59, 108, 157 },     //palm_center -> thumb_pip

	//thumb
	{ 254, 61, 253 },     //thumb_pip -> thumb_dip
	{ 198, 246, 205 }     //thumb_dip -> thumb_tip


};

const int skeleton_color_bone_gt_MSRA[BoneNum_MSRA][3] =
{
	//index finger
	{ 23, 139, 139 },   //imcp -> wrist
	{ 9, 9, 254 }, //ipip -> imcp
	{ 130, 55, 66 },   //idip -> ipip
	{ 254, 9, 254 },  //itip -> idip

	//middle finger
	{ 79, 21, 79 },     //mmcp -> wrist
	{ 8, 131, 254 },    //mpip -> mmcp
	{ 9, 254, 131 },     //mdip -> mpip
	{ 176, 97, 175 },     //mtip -> mdip

	//ring finger
	{ 234, 216, 155 },   //rmcp -> wrist
	{ 86, 121, 185 },     //rpip -> rmcp
	{ 205, 79, 69 },   //rdip -> rpip
	{ 231, 193, 201 },   //rtip -> rdip 

	//pinky finger
	{ 201, 177, 254 },   //pmcp -> wrist
	{ 78, 178, 37 },     //ppip -> pmcp
	{ 82, 246, 255 },   //pdip -> ppip
	{ 28, 10, 139 }, //ptip -> pdip 

	//thumb finger
	{ 153, 237, 243 }, //tmcp -> wrist
	{ 63, 80, 58 },    //tpip -> tmcp
	{ 9, 73, 181 }, //tdip -> tpip
	{ 138, 254, 138 },   //ttip -> tdip
};

const int skeleton_color_bone_gt_ICVL[BoneNum_ICVL][3] =
{
	//pinky
	{ 204, 72, 63 }, //pinky_tip_ICVL -> pinky_pip_ICVL
	{ 36, 28, 237 },     //pinky_pip_ICVL -> pinky_mcp_ICVL
	{ 87, 121, 185 },  //pinky_mcp_ICVL -> palm_center

	//ring
	{ 0, 242, 255 },   //ring_tip_ICVL -> ring_pip_ICVL
	{ 164, 73, 163 },     //ring_pip_ICVL -> ring_mcp_ICVL
	{ 198, 198, 198 },   //ring_mcp_ICVL -> palm_center

	//middle
	{ 76, 177, 34 },     //middle_tip_ICVL -> middle_pip_ICVL
	{ 201, 174, 255 },    //middle_pip_ICVL -> middle_mcp_ICVL
	{ 234, 216, 154 },     //middle_mcp_ICVL -> palm_center

	//index
	{ 21, 0, 136 },  //index_tip_ICVL -> index_pip_ICVL
	{ 29, 230, 181 }, //index_pip_ICVL -> index_mcp_ICVL
	{ 51, 134, 154 },   //index_mcp_ICVL -> palm_center

	//thumb
	{ 128, 3, 253 },   //thumb_tip_ICVL -> thumb_dip_ICVL
	{ 9, 254, 9 }, //thumb_dip_ICVL -> thumb_mcp_ICVL
	{ 171, 171, 129 }, //thumb_mcp_ICVL -> palm_center

};

const int skeleton_color_bone_gt[BoneNum][3] =
{
	{ 138, 254, 138 },   //ttip -> tdip
	{ 9, 73, 181 },      //tdip -> tpip//tdip -> tpip
	{ 63, 80, 58 },      //tpip -> tmcp
	{ 153, 237, 243 },   //tmcp -> wrist

	{ 254, 9, 254 },     //itip -> idip
	{ 130, 55, 66 },     //idip -> ipip
	{ 9, 9, 254 },       //ipip -> imcp
	{ 23, 139, 139 },    //imcp -> wrist

	{ 176, 97, 175 },    //mtip -> mdip
	{ 9, 254, 131 },     //mdip -> mpip
	{ 8, 131, 254 },     //mpip -> mmcp
	{ 79, 21, 79 },      //mmcp -> wrist

	{ 231, 193, 201 },   //rtip -> rdip 
	{ 205, 79, 69 },     //rdip -> rpip
	{ 86, 121, 185 },    //rpip -> rmcp
	{ 234, 216, 155 },   //rmcp -> wrist

	{ 28, 10, 139 },     //ptip -> pdip 
	{ 82, 246, 255 },    //pdip -> ppip
	{ 78, 178, 37 },     //ppip -> pmcp
	{ 201, 177, 254 },   //pmcp -> wrist

};

const int NYU_joints[JointNum_NYU_Eval] =
{
	little_finger_tip, little_finger_pip_first,
	ring_finger_tip, ring_finger_pip_first,
	middle_finger_tip, middle_finger_pip_first,
	index_finger_tip, index_finger_pip_first,
	palm_center,
	wrist_left, wrist_middle,
	thumb_pip, thumb_dip, thumb_tip
};


//extern from main function
double deg2rad(double deg);
double rad2deg(double rad);

extern bool current_image_not_null; //if null then optimization will not proceed
extern double opt_location[JointNum * 3];
extern double opt_projection[JointNum * 2];
extern double opt_param[ParamNum];
extern char directory[maxlen];

const char xyz_name[3][maxlen] =
{
	"x",
	"y",
	"z"
};


const char joint_NYU_name[JointNum_NYU][maxlen] =
{
	"little_finger_tip", "little_finger_dip", "little_finger_pip_second", "little_finger_pip_first", "little_finger_base",
	"ring_finger_tip", "ring_finger_dip", "ring_finger_pip_second", "ring_finger_pip_first", "ring_finger_base",
	"middle_finger_tip", "middle_finger_dip", "middle_finger_pip_second", "middle_finger_pip_first", "middle_finger_base",
	"index_finger_tip", "index_finger_dip", "index_finger_pip_second", "index_finger_pip_first", "index_finger_base",
	"little_finger_mcp", "ring_finger_mcp", "middle_finger_mcp", "index_finger_mcp", "palm_center", "wrist_left", "wrist_middle",
	"thumb_mcp", "thumb_pip", "thumb_dip", "thumb_tip"
};


const char joint_NYU_Eval_name[JointNum_NYU_Eval][maxlen] =
{
	"little_finger_tip",   "little_finger_pip_first", 
	"ring_finger_tip",  "ring_finger_pip_first", 
	"middle_finger_tip", "middle_finger_pip_first", 
	"index_finger_tip",  "index_finger_pip_first", 
	 "palm_center", "wrist_left", "wrist_middle",
	 "thumb_pip", "thumb_dip", "thumb_tip"
};


const char joint_MSRA_name[JointNum_MSRA][maxlen] =
{
	"wrist_MSRA", "imcp_MSRA", "ipip_MSRA", "idip_MSRA", "itip_MSRA",
	"mmcp_MSRA", "mpip_MSRA", "mdip_MSRA", "mtip_MSRA",
	"rmcp_MSRA", "rpip_MSRA", "rdip_MSRA", "rtip_MSRA",
	"pmcp_MSRA", "ppip_MSRA", "pdip_MSRA", "ptip_MSRA",
	"tmcp_MSRA", "tpip_MSRA", "tdip_MSRA", "ttip_MSRA"
};

const char joint_ICVL_name[JointNum_ICVL][maxlen] =
{
	"palm_center_ICVL", "thumb_mcp_ICVL", "thumb_dip_ICVL", "thumb_tip_ICVL", "index_mcp_ICVL",
	"index_pip_ICVL",	"index_tip_ICVL", "middle_mcp_ICVL", "middle_pip_ICVL", "middle_tip_ICVL",
	"ring_mcp_ICVL", "ring_pip_ICVL", "ring_tip_ICVL", "pinky_mcp_ICVL", "pinky_pip_ICVL", "pinky_tip_ICVL"
};


const char joint_name[JointNum][maxlen] =
{
	"wrist", "tmcp", "imcp", "mmcp", "rmcp", "pmcp",
	"tpip", "tdip", "ttip",
	"ipip", "idip", "itip",
	"mpip", "mdip", "mtip",
	"rpip", "rdip", "rtip",
	"ppip", "pdip", "ptip"
};

const char param_name[ParamNum][maxlen] =
{
	"global_trans_x", "global_trans_y", "global_trans_z", "global_rot_x", "global_rot_y", "global_rot_z",
	"thumb_mcp_rot_y", "thumb_mcp_rot_z", "thumb_pip_rot_y", "thumb_dip_rot_y",
	"index_mcp_rot_x", "index_mcp_rot_z", "index_pip_rot_x", "index_dip_rot_x",
	"middle_mcp_rot_x", "middle_mcp_rot_z", "middle_pip_rot_x", "middle_dip_rot_x",
	"ring_mcp_rot_x", "ring_mcp_rot_z", "ring_pip_rot_x", "ring_dip_rot_x",
	"pinky_mcp_rot_x", "pinky_mcp_rot_z", "pinky_pip_rot_x", "pinky_dip_rot_x",
	//untunable
	"thumb_mcp_const_rot_x", "thumb_mcp_const_rot_y", "thumb_mcp_const_rot_z",
	"index_mcp_const_rot_x", "index_mcp_const_rot_y", "index_mcp_const_rot_z",
	"middle_mcp_const_rot_x", "middle_mcp_const_rot_y", "middle_mcp_const_rot_z",
	"ring_mcp_const_rot_x", "ring_mcp_const_rot_y", "ring_mcp_const_rot_z",
	"pinky_mcp_const_rot_x", "pinky_mcp_const_rot_y", "pinky_mcp_const_rot_z"
};

const char bone_NYU_name[BoneNum_NYU][maxlen] =
{
	//little finger:
	"bone_little_finger_tip_connect_dip", "bone_little_finger_dip_connect_pip_second", "bone_little_finger_pip_second_connect_pip_first", "bone_little_finger_pip_first_connect_finger_base", "bone_little_finger_base_connect_mcp",
	//ring finger:
	"bone_ring_finger_tip_connect_dip", "bone_ring_finger_dip_connect_pip_second", "bone_ring_finger_pip_second_connect_pip_first", "bone_ring_finger_pip_first_connect_finger_base, bone_ring_finger_base_connect_mcp",
	//middle finger:
	"bone_middle_finger_tip_connect_dip", "bone_middle_finger_dip_connect_pip_second", "bone_middle_finger_pip_second_connect_pip_first", "bone_middle_finger_pip_first_connect_finger_base", "bone_middle_finger_base_connect_mcp",
	//index finger:
	"bone_index_finger_tip_connect_dip", "bone_index_finger_dip_connect_pip_second", "bone_index_finger_pip_second_connect_pip_first", "bone_index_finger_pip_first_connect_finger_base", "bone_index_finger_base_connect_mcp",
	//4 MCP connect palm center
	"bone_little_finger_mcp_connect_palm_center", "bone_ring_finger_mcp_connect_palm_center", "bone_middle_finger_mcp_connect_palm_center", "bone_index_finger_mcp_connect_palm_center",
	"bone_palm_center_connect_wrist_left", "bone_palm_center_connect_wrist_middle", "bone_palm_center_connect_thumb_mcp",
	//thumb finger:
	"bone_thumb_mcp_connect_pip", "bone_thumb_pip_connect_dip", "bone_thumb_dip_connect_tip"
};

const char bone_MSRA_name[BoneNum_MSRA][maxlen] =
{
	"bone_imcp_MSRA_wrist_MSRA", "bone_ipip_MSRA_imcp_MSRA", "bone_idip_MSRA_ipip_MSRA", "bone_itip_MSRA_idip_MSRA", //index finger
	"bone_mmcp_MSRA_wrist_MSRA", "bone_mpip_MSRA_mmcp_MSRA", "bone_mdip_MSRA_mpip_MSRA", "bone_mtip_MSRA_mdip_MSRA", //middle finger
	"bone_rmcp_MSRA_wrist_MSRA", "bone_rpip_MSRA_rmcp_MSRA", "bone_rdip_MSRA_rpip_MSRA", "bone_rtip_MSRA_rdip_MSRA", //ring finger
	"bone_pmcp_MSRA_wrist_MSRA", "bone_ppip_MSRA_pmcp_MSRA", "bone_pdip_MSRA_ppip_MSRA", "bone_ptip_MSRA_pdip_MSRA"  //pinky finger	
};


const char bones_ICVL_name[BoneNum_ICVL][maxlen] =
{
	"bone_pinky_tip_pinky_pip_ICVL", "bone_pinky_pip_pinky_mcp_ICVL", "bone_pinky_mcp_palm_center_ICVL",
	"bone_ring_tip_ring_pip_ICVL", "bone_ring_pip_ring_mcp_ICVL", "bone_ring_mcp_palm_center_ICVL",
	"bone_middle_tip_middle_pip_ICVL", "bone_middle_pip_middle_mcp_ICVL", "bone_middle_mcp_palm_center_ICVL",
	"bone_index_tip_index_pip_ICVL", "bone_index_pip_index_mcp_ICVL", "bone_index_mcp_palm_center_ICVL",
	"bone_thumb_mcp_palm_center_ICVL", "bone_thumb_dip_thumb_mcp_ICVL", "bone_thumb_tip_thumb_dip_ICVL"
};

const char bone_name[BoneNum][maxlen] =
{
	"bone_ttip_tdip", "bone_tdip_tpip", "bone_tpip_tmcp", "bone_tmcp_wrist",  //thumb
	"bone_itip_idip", "bone_idip_ipip", "bone_ipip_imcp", "bone_imcp_wrist",  //index
	"bone_mtip_mdip", "bone_mdip_mpip", "bone_mpip_mmcp", "bone_mmcp_wrist",  //middle
	"bone_rtip_rdip", "bone_rdip_rpip", "bone_rpip_rmcp", "bone_rmcp_wrist",  //ring
	"bone_ptip_pdip", "bone_pdip_ppip", "bone_ppip_pmcp", "bone_pmcp_wrist"   //pinky(little)	
};

//hyper parameters

void normalize_depth(cv::Mat &img, int bbx_x1, int bbx_y1, int bbx_x2, int bbx_y2);
void plotBoundingBox(double bbx_x1, double bbx_y1, double bbx_x2, double bbx_y2, cv::Mat img, cv::Scalar color_line_0, cv::Scalar color_line_1, cv::Scalar color_line_2, cv::Scalar color_line_3);



double shift_ratio(char *directory);
double show_image_size(char *directory);
double sphere_radius(char *directory);
double circle_radius(char *directory);
double line_width_2d(char *directory);
double line_width_3d(char *directory);
double mul_factor(char *directory);
bool fig_edges(char *directory);
double randuniform();
void ConvertDepth(cv::Mat src, cv::Mat &out);
void RotImage(cv::Mat src, cv::Mat &out, double alpha);
void ScaleImage(cv::Mat src, cv::Mat &out, double scale_factor);
void TranslateImage(cv::Mat src, cv::Mat &out, double delta_u, double delta_v);
void plotSingleJoint(int radius, int thickness, cv::Mat img, double *t_joint_2d);
void plotSingleJointICVL(int radius, int thickness, cv::Mat img, double *t_joint_2d);
void connecteEdge(int thickness, cv::Mat img, double *t_joint_2d);


//get the interplotated value
double *BilinearInterpolation(cv::Mat src, double u, double v);

//get the projection after rotation
double *ProjAfterRotation(double u, double v, int w, int h, double alpha);

//get the projection after scaling
double *ProjAfterScaling(double u, double v, int w, int h, double scale_factor);

//get the projection after translation
double *ProjAfterTranslation(double u, double v, double delta_u, double delta_v);

//Local contrast normalization
void LocalContrastNormalization(cv::Mat src, cv::Mat &out, int bbx_x1, int bbx_y1, int bbx_x2, int bbx_y2, int *local_patch_window, int patch_num, bool on_raw_depth, int depth_now_lb, int depth_now_ub);