#pragma once
#define pb push_back
#define mp std::make_pair
#include <cstring>
using namespace std;
enum basic_settings {
	JointNum = 21, BoneNum = 20, ParamNum = 41,
	PairNum = 210, ConstMatrNum = 21,
	//JointNum * (JointNum - 1) = 21 * 20 / 2

	JointNum_NYU = 31, JointNum_NYU_Eval = 14,
	BoneNum_NYU = 30, BoneNum_NYU_Eval = 13,

	ParamNum_NYU = 47,/*While Our hand Model fixes the seven joints namely "Bone_1_MCP, Bone_2_MCP, Bone_3_MCP, Bone_4_MCP, wrist_left, wrist_middle, thumb_MCP" on the palm,
					  the following dimensions : 6-14, 19-30 are fixed in order to keep the relative spatial relationships of the seven joints.
					  Therefore our hand model actually has 26 tunable DoFs: dimension 0-5, 15-18, 31-46*/

					  ConstMatrNum_NYU = JointNum_NYU,
					  EachFingerBoneNum_NYU = 5,
					  EachMCPDoFNum_NYU = 3,
					  EachFingerDoFNum_NYU = 4,
					  PairNum_NYU = 465,

					  JointNum_MSRA = 21, BoneNum_MSRA = 20, ParamNum_MSRA = 41,
					  PairNum_MSRA = 210, ConstMatrNum_MSRA = 21,
	JointNum_ICVL = 16, BoneNum_ICVL = 15
};

enum joint // 21
{
	wrist, tmcp, imcp, mmcp, rmcp, pmcp,
	tpip, tdip, ttip,                    //thumb
	ipip, idip, itip,                    //index
	mpip, mdip, mtip,                    //middle
	rpip, rdip, rtip,                    //ring
	ppip, pdip, ptip                     //pinky(little)

};

enum joint_MSRA // 21 different sequence
{
	wrist_MSRA, imcp_MSRA, ipip_MSRA, idip_MSRA, itip_MSRA,
	mmcp_MSRA, mpip_MSRA, mdip_MSRA, mtip_MSRA,
	rmcp_MSRA, rpip_MSRA, rdip_MSRA, rtip_MSRA,
	pmcp_MSRA, ppip_MSRA, pdip_MSRA, ptip_MSRA,
	tmcp_MSRA, tpip_MSRA, tdip_MSRA, ttip_MSRA
};


enum joint_NYU //31
{
	//little finger:
	little_finger_tip, little_finger_dip, little_finger_pip_second, little_finger_pip_first, little_finger_base,
	//ring finger:
	ring_finger_tip, ring_finger_dip, ring_finger_pip_second, ring_finger_pip_first, ring_finger_base,
	//middle finger:
	middle_finger_tip, middle_finger_dip, middle_finger_pip_second, middle_finger_pip_first, middle_finger_base,
	//index finger:
	index_finger_tip, index_finger_dip, index_finger_pip_second, index_finger_pip_first, index_finger_base,
	//4 MCP:
	little_finger_mcp, ring_finger_mcp, middle_finger_mcp, index_finger_mcp,
	palm_center,
	//the left 3 fixed joints:
	wrist_left, wrist_middle, thumb_mcp,
	//thumb finger:
	thumb_pip, thumb_dip, thumb_tip
};

enum joint_ICVL //16
{
	palm_center_ICVL,     //0  Palm
	thumb_mcp_ICVL,       //1  Thumb root
	thumb_dip_ICVL,       //2  Thumb mid
	thumb_tip_ICVL,       //3  Thumb tip
	index_mcp_ICVL,       //4  Index root
	index_pip_ICVL,       //5  Index mid
	index_tip_ICVL,       //6  Index tip
	middle_mcp_ICVL,      //7  Middle root
	middle_pip_ICVL,      //8  Middle mid
	middle_tip_ICVL,      //9  Middle tip
	ring_mcp_ICVL,        //10 Ring root
	ring_pip_ICVL,        //11 Ring mid
	ring_tip_ICVL,        //12 Ring tip
	pinky_mcp_ICVL,       //13 Pinky root
	pinky_pip_ICVL,       //14 Pinky mid
	pinky_tip_ICVL        //15 Pinky tip
};

enum bone // 20
{
	bone_ttip_tdip, bone_tdip_tpip, bone_tpip_tmcp, bone_tmcp_wrist,  //thumb
	bone_itip_idip, bone_idip_ipip, bone_ipip_imcp, bone_imcp_wrist,  //index
	bone_mtip_mdip, bone_mdip_mpip, bone_mpip_mmcp, bone_mmcp_wrist,  //middle
	bone_rtip_rdip, bone_rdip_rpip, bone_rpip_rmcp, bone_rmcp_wrist,  //ring
	bone_ptip_pdip, bone_pdip_ppip, bone_ppip_pmcp, bone_pmcp_wrist   //pinky(little)	
};

enum bone_MSRA //20
{
	bone_imcp_wrist_MSRA, bone_ipip_imcp_MSRA, bone_idip_ipip_MSRA, bone_itip_idip_MSRA, //index
	bone_mmcp_wrist_MSRA, bone_mpip_mmcp_MSRA, bone_mdip_mpip_MSRA, bone_mtip_mdip_MSRA, //middle
	bone_rmcp_wrist_MSRA, bone_rpip_rmcp_MSRA, bone_rdip_rpip_MSRA, bone_rtip_rdip_MSRA, //ring
	bone_pmcp_wrist_MSRA, bone_ppip_pmcp_MSRA, bone_pdip_ppip_MSRA, bone_ptip_pdip_MSRA, //pinky
	bone_tmcp_wrist_MSRA, bone_tpip_tmcp_MSRA, bone_tdip_tpip_MSRA, bone_ttip_tdip_MSRA  //thumb
};

enum bone_NYU //30
{
	//little finger:
	bone_little_finger_tip_connect_dip, bone_little_finger_dip_connect_pip_second, bone_little_finger_pip_second_connect_pip_first, bone_little_finger_pip_first_connect_finger_base, bone_little_finger_base_connect_mcp,
	//ring finger:
	bone_ring_finger_tip_connect_dip, bone_ring_finger_dip_connect_pip_second, bone_ring_finger_pip_second_connect_pip_first, bone_ring_finger_pip_first_connect_finger_base, bone_ring_finger_base_connect_mcp,
	//middle finger:
	bone_middle_finger_tip_connect_dip, bone_middle_finger_dip_connect_pip_second, bone_middle_finger_pip_second_connect_pip_first, bone_middle_finger_pip_first_connect_finger_base, bone_middle_finger_base_connect_mcp,
	//index finger:
	bone_index_finger_tip_connect_dip, bone_index_finger_dip_connect_pip_second, bone_index_finger_pip_second_connect_pip_first, bone_index_finger_pip_first_connect_finger_base, bone_index_finger_base_connect_mcp,
	//4 MCP connect palm center
	bone_little_finger_mcp_connect_palm_center, bone_ring_finger_mcp_connect_palm_center, bone_middle_finger_mcp_connect_palm_center, bone_index_finger_mcp_connect_palm_center,
	bone_palm_center_connect_wrist_left, bone_palm_center_connect_wrist_middle, bone_palm_center_connect_thumb_mcp,
	//thumb finger:
	bone_thumb_mcp_connect_pip, bone_thumb_pip_connect_dip, bone_thumb_dip_connect_tip
};

enum bone_ICVL //15
{
	bone_pinky_tip_pinky_pip_ICVL, bone_pinky_pip_pinky_mcp_ICVL, bone_pinky_mcp_palm_center_ICVL,
	bone_ring_tip_ring_pip_ICVL, bone_ring_pip_ring_mcp_ICVL, bone_ring_mcp_palm_center_ICVL,
	bone_middle_tip_middle_pip_ICVL, bone_middle_pip_middle_mcp_ICVL, bone_middle_mcp_palm_center_ICVL,
	bone_index_tip_index_pip_ICVL, bone_index_pip_index_mcp_ICVL, bone_index_mcp_palm_center_ICVL,
	bone_thumb_mcp_palm_center_ICVL, bone_thumb_dip_thumb_mcp_ICVL, bone_thumb_tip_thumb_dip_ICVL
};

enum dof //26 + 15
{
	global_trans_x, global_trans_y, global_trans_z, global_rot_x, global_rot_y, global_rot_z,
	thumb_mcp_rot_y, thumb_mcp_rot_z, thumb_pip_rot_y, thumb_dip_rot_y,
	index_mcp_rot_x, index_mcp_rot_z, index_pip_rot_x, index_dip_rot_x,
	middle_mcp_rot_x, middle_mcp_rot_z, middle_pip_rot_x, middle_dip_rot_x,
	ring_mcp_rot_x, ring_mcp_rot_z, ring_pip_rot_x, ring_dip_rot_x,
	pinky_mcp_rot_x, pinky_mcp_rot_z, pinky_pip_rot_x, pinky_dip_rot_x,
	//untunable
	thumb_mcp_const_rot_x, thumb_mcp_const_rot_y, thumb_mcp_const_rot_z,
	index_mcp_const_rot_x, index_mcp_const_rot_y, index_mcp_const_rot_z,
	middle_mcp_const_rot_x, middle_mcp_const_rot_y, middle_mcp_const_rot_z,
	ring_mcp_const_rot_x, ring_mcp_const_rot_y, ring_mcp_const_rot_z,
	pinky_mcp_const_rot_x, pinky_mcp_const_rot_y, pinky_mcp_const_rot_z
};

enum dof_NYU //47(only 26 are tunable, while the left 21 are for fixing seven joints on the palm)
{
	//0-5: tunable
	global_trans_x_NYU, global_trans_y_NYU, global_trans_z_NYU, global_rot_x_NYU, global_rot_y_NYU, global_rot_z_NYU,
	//6-14 are fixed constants to fix wrist_left, wrist_middle and thumb_mcp
	wrist_left_const_rot_x_NYU, wrist_left_const_rot_y_NYU, wrist_left_const_rot_z_NYU, wrist_middle_const_rot_x_NYU, wrist_middle_const_rot_y_NYU, wrist_middle_const_rot_z_NYU, thumb_mcp_const_rot_x_NYU, thumb_mcp_const_rot_y_NYU, thumb_mcp_const_rot_z_NYU,
	//15-18: tunable
	thumb_pip_rot_y_NYU, thumb_pip_rot_z_NYU, thumb_dip_rot_z_NYU, thumb_tip_rot_z_NYU,
	//19-30 are fixed constants to fix 4 MCP joints of the four fingers(expect thumb finger)
	little_finger_mcp_const_rot_x_NYU, little_finger_mcp_const_rot_y_NYU, little_finger_mcp_const_rot_z_NYU,
	ring_finger_mcp_const_rot_x_NYU, ring_finger_mcp_const_rot_y_NYU, ring_finger_mcp_const_rot_z_NYU,
	middle_finger_mcp_const_rot_x_NYU, middle_finger_mcp_const_rot_y_NYU, middle_finger_mcp_const_rot_z_NYU,
	index_finger_mcp_const_rot_x_NYU, index_finger_mcp_const_rot_y_NYU, index_finger_mcp_const_rot_z_NYU,
	//31-46: tunable
	little_finger_base_rot_x_NYU, little_finger_base_rot_z_NYU, little_finger_pip_rot_x_NYU, little_finger_dip_rot_x_NYU,
	ring_finger_base_rot_x_NYU, ring_finger_base_rot_z_NYU, ring_finger_pip_rot_x_NYU, ring_finger_dip_rot_x_NYU,
	middle_finger_base_rot_x_NYU, middle_finger_base_rot_z_NYU, middle_finger_pip_rot_x_NYU, middle_finger_dip_rot_x_NYU,
	index_finger_base_rot_x_NYU, index_finger_base_rot_z_NYU, index_finger_pip_rot_x_NYU, index_finger_dip_rot_x_NYU
};


enum finger_joint_start_id {
	finger_tip_start = 0, //e.g. little_finger_tip = 0, ring_finger_tip = 5, middle_finger_tip = 10, index_finger_tip = 15(cycle is num of bones each finger : 5)
	finger_dip_start = 1, finger_pip_second_start = 2, finger_pip_first_start = 3, finger_base_start = 4,
	finger_mcp_start = 20,
};

enum bone_start_id {
	bone_finger_tip_connect_dip_start = 0, bone_finger_dip_connect_pip_second_start = 1, bone_finger_pip_second_connect_pip_first_start = 2, bone_finger_pip_first_connect_finger_base_start = 3, bone_finger_base_connect_finger_mcp_start = 4,
	bone_finger_mcp_connect_palm_center_start = 20,
};

enum dof_start_id {
	finger_mcp_rot_x_start = 19, finger_mcp_rot_y_start = 20, finger_mcp_rot_z_start = 21,
	finger_base_rot_x_start = 31, finger_base_rot_z_start = 32, finger_pip_rot_x_start = 33, finger_dip_rot_x_start = 34
};



const int joint_NYU_eval[JointNum_NYU_Eval] =
{
	little_finger_tip, little_finger_pip_first, ring_finger_tip, ring_finger_pip_first, middle_finger_tip, middle_finger_pip_first,
	index_finger_tip, index_finger_pip_first, palm_center, wrist_left, wrist_middle, thumb_pip, thumb_dip, thumb_tip


};

//all 30 bones
const int bones_NYU[BoneNum_NYU][2] =
{
	//little finger :
	{ little_finger_tip, little_finger_dip }, { little_finger_dip, little_finger_pip_second }, { little_finger_pip_second, little_finger_pip_first }, { little_finger_pip_first, little_finger_base }, { little_finger_base, little_finger_mcp }, { little_finger_mcp, palm_center },
	//ring finger :
	{ ring_finger_tip, ring_finger_dip }, { ring_finger_dip, ring_finger_pip_second }, { ring_finger_pip_second, ring_finger_pip_first },
	{ ring_finger_pip_first, ring_finger_base }, { ring_finger_base, ring_finger_mcp },
	{ ring_finger_mcp, palm_center },
	//middle finger:
	{ middle_finger_tip, middle_finger_dip }, { middle_finger_dip, middle_finger_pip_second }, { middle_finger_pip_second, middle_finger_pip_first }, { middle_finger_pip_first, middle_finger_base }, { middle_finger_base, middle_finger_mcp },
	{ middle_finger_mcp, palm_center },
	//index finger:
	{ index_finger_tip, index_finger_dip }, { index_finger_dip, index_finger_pip_second }, { index_finger_pip_second, index_finger_pip_first },
	{ index_finger_pip_first, index_finger_base }, { index_finger_base, index_finger_mcp },
	{ index_finger_mcp, palm_center },
	//the left 3 fixed joints:
	{ wrist_left, palm_center }, { wrist_middle, palm_center }, { thumb_mcp, palm_center },
	//thumb finger:
	{ thumb_pip, thumb_mcp }, { thumb_dip, thumb_pip }, { thumb_tip, thumb_dip }
};

//all 13 bones
const int bones_NYU_Eval[BoneNum_NYU][2] =
{
	//little finger :
	{ little_finger_tip, little_finger_pip_first }, { little_finger_pip_first, palm_center },
	//ring finger :
	{ ring_finger_tip, ring_finger_pip_first }, { ring_finger_pip_first, palm_center },
	//middle finger:
	{ middle_finger_tip, middle_finger_pip_first }, { middle_finger_pip_first, palm_center },
	//index finger:
	{ index_finger_tip, index_finger_pip_first }, { index_finger_pip_first, palm_center },
	//the left 3 fixed joints:
	{ wrist_left, palm_center }, { wrist_middle, palm_center }, { thumb_pip, palm_center },
	//thumb finger:
	{ thumb_dip, thumb_pip }, { thumb_tip, thumb_dip }
};

//MSRA
const int bones_MSRA[BoneNum_MSRA][2] =
{
	{ imcp_MSRA, wrist_MSRA }, { ipip_MSRA, imcp_MSRA }, { idip_MSRA, ipip_MSRA }, { itip_MSRA, idip_MSRA },
	{ mmcp_MSRA, wrist_MSRA }, { mpip_MSRA, mmcp_MSRA }, { mdip_MSRA, mpip_MSRA }, { mtip_MSRA, mdip_MSRA },
	{ rmcp_MSRA, wrist_MSRA }, { rpip_MSRA, rmcp_MSRA }, { rdip_MSRA, rpip_MSRA }, { rtip_MSRA, rdip_MSRA },
	{ pmcp_MSRA, wrist_MSRA }, { ppip_MSRA, pmcp_MSRA }, { pdip_MSRA, ppip_MSRA }, { ptip_MSRA, pdip_MSRA },
	{ tmcp_MSRA, wrist_MSRA }, { tpip_MSRA, tmcp_MSRA }, { tdip_MSRA, tpip_MSRA }, { ttip_MSRA, tdip_MSRA }
};

const int bones_ICVL[BoneNum_ICVL][2] =
{
	{ pinky_tip_ICVL, pinky_pip_ICVL }, { pinky_pip_ICVL, pinky_mcp_ICVL }, { pinky_mcp_ICVL, palm_center_ICVL },
	{ ring_tip_ICVL, ring_pip_ICVL }, { ring_pip_ICVL, ring_mcp_ICVL }, { ring_mcp_ICVL, palm_center_ICVL },
	{ middle_tip_ICVL, middle_pip_ICVL }, { middle_pip_ICVL, middle_mcp_ICVL }, { middle_mcp_ICVL, palm_center_ICVL },
	{ index_tip_ICVL, index_pip_ICVL }, { index_pip_ICVL, index_mcp_ICVL }, { index_mcp_ICVL, palm_center_ICVL },
	{ thumb_mcp_ICVL, palm_center_ICVL }, { thumb_dip_ICVL, thumb_mcp_ICVL }, { thumb_tip_ICVL, thumb_dip_ICVL }
};

const int bones[BoneNum][2] =
{
	{ ttip, tdip }, { tdip, tpip }, { tpip, tmcp }, { tmcp, wrist },
	{ itip, idip }, { idip, ipip }, { ipip, imcp }, { imcp, wrist },
	{ mtip, mdip }, { mdip, mpip }, { mpip, mmcp }, { mmcp, wrist },
	{ rtip, rdip }, { rdip, rpip }, { rpip, rmcp }, { rmcp, wrist },
	{ ptip, pdip }, { pdip, ppip }, { ppip, pmcp }, { pmcp, wrist }
};

const int forward_seq[JointNum] =
{
	wrist, tmcp, tpip, tdip, ttip, //thumb	
	imcp, ipip, idip, itip,        //index
	mmcp, mpip, mdip, mtip,        //middle
	rmcp, rpip, rdip, rtip,        //ring
	pmcp, ppip, pdip, ptip         //pinky		
};

const int prev_seq[JointNum] =
{
	-1, wrist, tmcp, tpip, tdip,
	wrist, imcp, ipip, idip,
	wrist, mmcp, mpip, mdip,
	wrist, rmcp, rpip, rdip,
	wrist, pmcp, ppip, pdip
};

const int forward_seq_MSRA[JointNum_MSRA] =
{
	wrist_MSRA, imcp_MSRA, ipip_MSRA, idip_MSRA, itip_MSRA, //index
	mmcp_MSRA, mpip_MSRA, mdip_MSRA, mtip_MSRA,             //middle
	rmcp_MSRA, rpip_MSRA, rdip_MSRA, rtip_MSRA,             //ring
	pmcp_MSRA, ppip_MSRA, pdip_MSRA, ptip_MSRA,             //pinky
	tmcp_MSRA, tpip_MSRA, tdip_MSRA, ttip_MSRA              //thumb
};

const int forward_seq_NYU[JointNum_NYU] =
{ palm_center, wrist_left, wrist_middle, thumb_mcp, thumb_pip, thumb_dip, thumb_tip, little_finger_mcp, ring_finger_mcp, middle_finger_mcp, index_finger_mcp,
little_finger_base, little_finger_pip_first, little_finger_pip_second, little_finger_dip, little_finger_tip,
ring_finger_base, ring_finger_pip_first, ring_finger_pip_second, ring_finger_dip, ring_finger_tip,
middle_finger_base, middle_finger_pip_first, middle_finger_pip_second, middle_finger_dip, middle_finger_tip,
index_finger_base, index_finger_pip_first, index_finger_pip_second, index_finger_dip, index_finger_tip
};

const int prev_seq_NYU[JointNum_NYU] =
{ -1, palm_center, palm_center, palm_center, thumb_mcp, thumb_pip, thumb_dip, palm_center, palm_center, palm_center, palm_center,
little_finger_mcp, little_finger_base, little_finger_pip_first, little_finger_pip_second, little_finger_dip,
ring_finger_mcp, ring_finger_base, ring_finger_pip_first, ring_finger_pip_second, ring_finger_dip,
middle_finger_mcp, middle_finger_base, middle_finger_pip_first, middle_finger_pip_second, middle_finger_dip,
index_finger_mcp, index_finger_base, index_finger_pip_first, index_finger_pip_second, index_finger_dip };


const int parent[JointNum] =
{
	-1,         //parent[wrist]=void
	wrist,     //parent[tmcp]=wrist
	wrist,     //parent[imcp]=wrist
	wrist,     //parent[mmcp]=wrist
	wrist,     //parent[rmcp]=wrist
	wrist,     //parent[pmcp]=wrist

	//T thumb
	tmcp,      //parent[tpip]=tmcp
	tpip,      //parent[tdip]=tpip
	tdip,      //parent[ttip]=tdip

	//I index
	imcp,      //parent[ipip]=imcp
	ipip,      //parent[idip]=ipip
	idip,      //parent[itip]=idip

	//M middle
	mmcp,      //parent[mpip]=mmcp
	mpip,      //parent[mdip]=mpip
	mdip,      //parent[mtip]=mdip

	//R ring
	rmcp,      //parent[rpip]=rmcp
	rpip,      //parent[rdip]=rpip
	rdip,      //parent[rtip]=rdip

	//P pinky (little
	pmcp,      //parent[ppip]=pmcp
	ppip,      //parent[pdip]=ppip
	pdip       //parent[ptip]=pdip

};

const int parent_MSRA[JointNum_MSRA] =
{
	-1,         //parent[wrist_MSRA]=void
	wrist_MSRA, //parent[imcp_MSRA]=wrist_MSRA
	imcp_MSRA,  //parent[ipip_MSRA]=imcp_MSRA
	ipip_MSRA,  //parent[idip_MSRA]=ipip_MSRA
	idip_MSRA,  //parent[itip_MSRA]=idip_MSRA

	wrist_MSRA, //parent[mmcp_MSRA]=wrist_MSRA
	mmcp_MSRA,  //parent[mpip_MSRA]=mmcp_MSRA
	mpip_MSRA,  //parent[mdip_MSRA]=mpip_MSRA
	mdip_MSRA,  //parent[mtip_MSRA]=mdip_MSRA

	wrist_MSRA, //parent[rmcp_MSRA]=wrist_MSRA
	rmcp_MSRA,  //parent[rpip_MSRA]=rmcp_MSRA
	rpip_MSRA,  //parent[rdip_MSRA]=rpip_MSRA
	rdip_MSRA,  //parent[rtip_MSRA]=rdip_MSRA

	wrist_MSRA, //parent[pmcp_MSRA]=wrist_MSRA
	pmcp_MSRA,  //parent[ppip_MSRA]=pmcp_MSRA
	ppip_MSRA,  //parent[pdip_MSRA]=ppip_MSRA
	pdip_MSRA,  //parent[ptip_MSRA]=pdip_MSRA

	wrist_MSRA, //parent[tmcp_MSRA]=wrist_MSRA
	tmcp_MSRA,  //parent[tpip_MSRA]=tmcp_MSRA
	tpip_MSRA,  //parent[tdip_MSRA]=tpip_MSRA
	tdip_MSRA,  //parent[ttip_MSRA]=tdip_MSRA
};


const int parent_NYU[JointNum_NYU] =
{
	little_finger_dip,                        //parent[little_finger_tip]=little_finger_dip
	little_finger_pip_second,                 //parent[little_finger_dip]=little_finger_pip_second
	little_finger_pip_first,                  //parent[little_finger_pip_second]=little_finger_pip_first
	little_finger_base,                       //parent[little_finger_pip_first]=little_finger_base
	little_finger_mcp,                        //parent[little_finger_base]=little_finger_mcp

	ring_finger_dip,                        //parent[ring_finger_tip]=ring_finger_dip
	ring_finger_pip_second,                 //parent[ring_finger_dip]=ring_finger_pip_second
	ring_finger_pip_first,                  //parent[ring_finger_pip_second]=ring_finger_pip_first
	ring_finger_base,                       //parent[ring_finger_pip_first]=ring_finger_base
	ring_finger_mcp,                        //parent[ring_finger_base]=ring_finger_mcp

	middle_finger_dip,                        //parent[middle_finger_tip]=middle_finger_dip
	middle_finger_pip_second,                 //parent[middle_finger_dip]=middle_finger_pip_second
	middle_finger_pip_first,                  //parent[middle_finger_pip_second]=middle_finger_pip_first
	middle_finger_base,                       //parent[middle_finger_pip_first]=middle_finger_base
	middle_finger_mcp,                        //parent[middle_finger_base]=middle_finger_mcp

	index_finger_dip,                        //parent[index_finger_tip]=index_finger_dip
	index_finger_pip_second,                 //parent[index_finger_dip]=index_finger_pip_second
	index_finger_pip_first,                  //parent[index_finger_pip_second]=idnex_finger_pip_first
	index_finger_base,                       //parent[index_finger_pip_first]=index_finger_base
	index_finger_mcp,                        //parent[index_finger_base]=index_finger_mcp

	palm_center,                             //parent[little_finger_mcp]=palm_center
	palm_center,                             //parent[ring_finger_mcp]=palm_center
	palm_center,                             //parent[middle_finger_mcp]=palm_center
	palm_center,                             //parent[index_finger_mcp]=palm_center

	-1,                                      //parent[palm_center]=void
	palm_center,                             //parent[wrist_left]=palm_center
	palm_center,                             //parent[wrist_middle]=palm_center
	palm_center,                             //parent[thumb_mcp]=palm_center
	thumb_mcp,                               //parent[thumb_pip]=thumb_mcp
	thumb_pip,                               //parent[thumb_dip]=thumb_pip
	thumb_dip,                               //parent[thumb_tip]=thumb_dip
};


//preserves the depth in the hierarchical tree level
const int level[JointNum] =
{
	0,         //level[wrist]=0
	1,         //level[tmcp]=1
	1,         //level[imcp]=1
	1,         //level[mmcp]=1
	1,         //level[rmcp]=1
	1,         //level[pmcp]=1

	//T thumb
	2,         //level[tpip]=2
	3,         //level[tdip]=3
	4,         //level[ttip]=4

	//I index
	2,         //level[ipip]=2
	3,         //level[idip]=3
	4,         //level[itip]=4

	//M middle
	2,         //level[mpip]=2
	3,         //level[mdip]=3
	4,         //level[mtip]=4

	//R ring
	2,         //level[rpip]=2
	3,         //level[rdip]=3
	4,         //level[rtip]=4

	//P pinky
	2,         //level[ppip]=2
	3,         //level[pdip]=3
	4          //level[ptip]=4
};

//preserves the depth in the hierarchical tree level
const int level_MSRA[JointNum_MSRA] =
{
	0,         //level[wrist]=0
	1,         //level[imcp]=1
	2,         //level[ipip]=2
	3,         //level[idip]=3
	4,         //level[itip]=4

	1,         //level[mmcp]=1
	2,         //level[mpip]=2
	3,         //level[mdip]=3
	4,         //level[mtip]=4

	1,         //level[rmcp]=1
	2,         //level[rpip]=2
	3,         //level[rdip]=3
	4,         //level[rtip]=4

	1,         //level[pmcp]=1
	2,         //level[ppip]=2
	3,         //level[pdip]=3
	4,         //level[ptip]=4

	1,         //level[tmcp]=1
	2,         //level[tpip]=2
	3,         //level[tdip]=3
	4,         //level[ttip]=4
};

//preserves the depth in the hierarchical tree level NYU
const int level_NYU[JointNum_NYU] =
{
	//little finger
	6,         //level[little_finger_tip]=6
	5,         //level[little_finger_dip]=5
	4,         //level[little_finger_pip_second]=4
	3,         //level[little_finger_pip_first]=3
	2,         //level[little_finger_base]=2
	1,         //level[little_finger_mcp]=1

	//ring finger
	6,         //level[ring_finger_tip]=6
	5,         //level[ring_finger_dip]=5
	4,         //level[ring_finger_pip_second]=4
	3,         //level[ring_finger_pip_first]=3
	2,         //level[ring_finger_base]=2
	1,         //level[ring_finger_mcp]=1

	//middle finger
	6,         //level[middle_finger_tip]=6
	5,         //level[middle_finger_dip]=5
	4,         //level[middle_finger_pip_second]=4
	3,         //level[middle_finger_pip_first]=3
	2,         //level[middle_finger_base]=2
	1,         //level[middle_finger_mcp]=1

	//index finger
	6,         //level[index_finger_tip]=6
	5,         //level[index_finger_dip]=5
	4,         //level[index_finger_pip_second]=4
	3,         //level[index_finger_pip_first]=3
	2,         //level[index_finger_base]=2
	1,         //level[index_finger_mcp]=1

	0,         //level[palm_center]=0
	1,         //level[wrist_left]=1
	1,         //level[wrist_middle]=1
	1,         //level[thumb_mcp]=1
	2,         //level[thumb_pip]=2
	3,         //level[thumb_dip]=3
	4,         //level[thumb_tip]=4

};