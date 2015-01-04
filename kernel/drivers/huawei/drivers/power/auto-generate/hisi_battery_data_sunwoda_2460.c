
/* DO NOT EDIT - Generated automatically by build.py */

static struct single_row_lut sunwoda_2460_fcc_temp = {
	.x		= {-20, -10, 0, 25, 40, 60},
	.y		= {2494, 2492, 2493, 2504, 2488, 2477},
	.cols	= 6
};

static struct single_row_lut sunwoda_2460_fcc_sf = {
	.x		= {0, 100, 200, 300, 400, 500},
	.y		= {100, 96, 94, 92, 90, 88},
	.cols	= 6
};

static struct sf_lut sunwoda_2460_pc_sf = {
	.rows = 1,
	.cols = 1,
	.row_entries = {0},
	.percent = {100},
	.sf = {
		{100}
	}
};


static struct sf_lut sunwoda_2460_rbatt_sf = {
	.rows = 28,
	.cols = 6,
	.row_entries = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf = {
		{3234, 2070, 1053, 235, 151, 130},
		{3231, 2069, 1053, 235, 151, 130},
		{2980, 1977, 1038, 239, 153, 131},
		{2825, 1886, 1018, 243, 156, 134},
		{2692, 1851, 1048, 250, 160, 136},
		{2514, 1647, 1001, 271, 167, 139},
		{2494, 1633, 906, 272, 175, 143},
		{2482, 1632, 910, 297, 186, 151},
		{2482, 1632, 880, 278, 205, 166},
		{2497, 1627, 878, 229, 156, 134},
		{2529, 1654, 886, 224, 150, 132},
		{2581, 1686, 902, 226, 153, 134},
		{2651, 1744, 951, 233, 158, 136},
		{2740, 1804, 1014, 238, 164, 143},
		{2856, 1882, 1092, 240, 162, 142},
		{3009, 1990, 1171, 242, 155, 135},
		{2955, 2141, 1267, 246, 152, 132},
		{2023, 2361, 1392, 251, 155, 133},
		{5623, 2753, 1417, 253, 159, 136},
		{6256, 2984, 1326, 248, 162, 141},
		{6605, 3214, 1414, 253, 161, 138},
		{6838, 3447, 1530, 258, 158, 137},
		{7254, 3670, 1679, 256, 157, 136},
		{7283, 3886, 1776, 259, 156, 136},
		{7652, 4086, 1783, 263, 156, 135},
		{8549, 4205, 1929, 272, 160, 136},
		{9474, 4569, 1935, 302, 165, 138},
		{11409, 5055, 2387, 726, 176, 195},
	}
};

static struct pc_temp_ocv_lut sunwoda_2460_pc_temp_ocv = {
	.rows = 29,
	.cols = 6,
	.temp = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv = {
		{4319, 4317, 4316, 4307, 4300, 4294},
		{4226, 4232, 4237, 4242, 4239, 4235},
		{4158, 4170, 4178, 4186, 4183, 4180},
		{4106, 4115, 4124, 4134, 4130, 4127},
		{4048, 4072, 4082, 4083, 4080, 4077},
		{3972, 3984, 4023, 4040, 4034, 4030},
		{3929, 3941, 3956, 3981, 3990, 3988},
		{3892, 3905, 3921, 3953, 3952, 3950},
		{3860, 3872, 3881, 3908, 3914, 3913},
		{3834, 3843, 3849, 3862, 3863, 3862},
		{3814, 3821, 3823, 3833, 3835, 3834},
		{3796, 3802, 3805, 3812, 3813, 3813},
		{3781, 3787, 3792, 3794, 3796, 3795},
		{3767, 3771, 3782, 3780, 3782, 3781},
		{3755, 3757, 3771, 3768, 3767, 3764},
		{3743, 3742, 3755, 3756, 3751, 3740},
		{3731, 3730, 3736, 3739, 3732, 3720},
		{3720, 3717, 3715, 3711, 3705, 3693},
		{3687, 3699, 3702, 3689, 3681, 3671},
		{3682, 3693, 3698, 3687, 3680, 3670},
		{3676, 3687, 3694, 3686, 3679, 3669},
		{3664, 3680, 3691, 3684, 3677, 3667},
		{3652, 3669, 3687, 3679, 3674, 3663},
		{3618, 3654, 3676, 3664, 3661, 3649},
		{3568, 3631, 3648, 3624, 3630, 3613},
		{3523, 3591, 3604, 3567, 3579, 3560},
		{3468, 3533, 3530, 3487, 3508, 3489},
		{3381, 3437, 3423, 3374, 3402, 3381},
		{3200, 3200, 3200, 3200, 3200, 3200},
	}
};

struct hisi_smartstar_coul_battery_data sunwoda_2460_battery_data = {
	.id_voltage_min = 1850,  // 200K
	.id_voltage_max = 2050,
	.fcc = 2460,
	.fcc_temp_lut  = &sunwoda_2460_fcc_temp,
	.fcc_sf_lut = &sunwoda_2460_fcc_sf,
	.pc_temp_ocv_lut = &sunwoda_2460_pc_temp_ocv,
	.pc_sf_lut = &sunwoda_2460_pc_sf,
	.rbatt_sf_lut = &sunwoda_2460_rbatt_sf,
	.default_rbatt_mohm = 100,
	.max_currentmA = 1000,
    .max_voltagemV = 4352,
    .max_cin_currentmA = 1200,
    .terminal_currentmA = 100,
    .charge_in_temp_5 = 3,
    .charge_in_temp_10 = 3,
    .batt_brand = "Sunwoda",
};
