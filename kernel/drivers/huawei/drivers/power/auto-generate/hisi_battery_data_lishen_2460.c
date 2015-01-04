
/* DO NOT EDIT - Generated automatically by battery_para_gen.pl */




static struct single_row_lut lishen_2460_fcc_temp = {
	.x		= {-20, -10, 0, 25, 40, 60},
	.y		= {2399, 2399, 2399, 2417, 2409, 2395},
	.cols	= 6
};


static struct single_row_lut lishen_2460_fcc_sf = {
	.x		= {0, 100, 200, 300, 400, 500},
	.y		= {100, 96, 94, 92, 90, 88},
	.cols	= 6
};


static struct sf_lut lishen_2460_pc_sf = {
	.rows = 1,
	.cols = 1,
	.row_entries = {0},
	.percent = {100},
	.sf = {
		{100}
	}
};


static struct sf_lut lishen_2460_rbatt_sf = {
	.rows = 28,
	.cols = 6,
	.row_entries = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf = {
		{1772, 827, 381, 100, 71, 62},
		{1778, 828, 381, 102, 71, 63},
		{1725, 828, 389, 105, 72, 63},
		{1670, 822, 392, 107, 73, 64},
		{1612, 844, 424, 111, 75, 65},
		{1480, 757, 408, 120, 78, 66},
		{1483, 741, 373, 121, 81, 68},
		{1494, 751, 381, 135, 87, 71},
		{1503, 755, 371, 130, 94, 76},
		{1526, 777, 374, 105, 77, 67},
		{1553, 802, 387, 101, 72, 64},
		{1585, 838, 408, 104, 72, 65},
		{1626, 875, 435, 107, 74, 65},
		{1677, 925, 470, 108, 78, 68},
		{1744, 992, 506, 110, 77, 68},
		{2234, 1072, 551, 111, 73, 65},
		{2614, 1176, 616, 112, 72, 63},
		{3050, 1304, 728, 115, 73, 63},
		{3758, 1489, 913, 125, 75, 65},
		{3972, 1512, 832, 120, 77, 66},
		{4169, 1475, 874, 123, 77, 69},
		{4414, 1673, 982, 122, 77, 67},
		{4689, 1836, 1084, 126, 76, 66},
		{4927, 2015, 1177, 126, 75, 64},
		{5304, 2226, 1231, 123, 75, 66},
		{5640, 2446, 1436, 131, 78, 66},
		{6123, 2728, 1678, 146, 81, 66},
		{6844, 3213, 2113, 214, 84, 68},
	}
};


static struct pc_temp_ocv_lut lishen_2460_pc_temp_ocv = {
	.rows = 29,
	.cols = 6,
	.temp = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv = {
		{4320, 4319, 4317, 4313, 4307, 4301},
		{4227, 4233, 4238, 4247, 4245, 4241},
		{4160, 4170, 4178, 4191, 4188, 4184},
		{4104, 4115, 4124, 4137, 4134, 4131},
		{4047, 4072, 4085, 4087, 4084, 4081},
		{3964, 3989, 4015, 4045, 4039, 4035},
		{3923, 3939, 3957, 3985, 3994, 3992},
		{3890, 3904, 3922, 3957, 3956, 3954},
		{3860, 3869, 3883, 3912, 3916, 3914},
		{3836, 3842, 3850, 3867, 3870, 3870},
		{3816, 3820, 3825, 3837, 3839, 3839},
		{3799, 3804, 3806, 3815, 3816, 3816},
		{3783, 3791, 3793, 3798, 3798, 3797},
		{3768, 3778, 3783, 3782, 3783, 3782},
		{3755, 3767, 3772, 3770, 3768, 3765},
		{3746, 3753, 3759, 3759, 3751, 3741},
		{3730, 3736, 3741, 3741, 3732, 3720},
		{3709, 3715, 3720, 3710, 3704, 3692},
		{3686, 3695, 3694, 3688, 3682, 3673},
		{3682, 3691, 3689, 3686, 3679, 3669},
		{3673, 3684, 3683, 3685, 3678, 3668},
		{3663, 3679, 3678, 3682, 3676, 3666},
		{3649, 3670, 3672, 3677, 3672, 3662},
		{3626, 3655, 3660, 3658, 3656, 3646},
		{3599, 3631, 3636, 3617, 3621, 3608},
		{3557, 3590, 3592, 3561, 3569, 3557},
		{3498, 3527, 3528, 3486, 3500, 3488},
		{3409, 3431, 3432, 3378, 3398, 3387},
		{3200, 3200, 3200, 3200, 3200, 3200},
	}
};


struct hisi_smartstar_coul_battery_data lishen_2460_battery_data = {
	.id_voltage_min = 850,  // 39K
	.id_voltage_max = 1050,
	.fcc = 2460,
	.fcc_temp_lut  = &lishen_2460_fcc_temp,
	.fcc_sf_lut = &lishen_2460_fcc_sf,
	.pc_temp_ocv_lut = &lishen_2460_pc_temp_ocv,
	.pc_sf_lut = &lishen_2460_pc_sf,
	.rbatt_sf_lut = &lishen_2460_rbatt_sf,
	.default_rbatt_mohm = 167,
	.max_currentmA = 1000,
    .max_voltagemV = 4352,
    .max_cin_currentmA = 1200,
    .terminal_currentmA = 100,
    .charge_in_temp_5 = 3,
    .charge_in_temp_10 = 3,
    .batt_brand = "LiShen",
};
