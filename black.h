/*
RobboLito is a UCI chess playing engine by
Yakov Petrovich Golyadkin, Igor Igorovich Igoronov, Roberto Pescatore
copyright: (C) 2009 Yakov Petrovich Golyadkin
date: 92th and 93rd year from Revolution
owners: PUBLICDOMAIN (workers)
dedication: To Vladimir Ilyich

RobboLito is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

RobboLito is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.
*/

#define my_pv_search_fine pv_search_fine_black
#define my_pv_search_fine_check pv_search_fine_check_black
#define my_search_fine_check search_fine_check_black
#define my_search_fine search_fine_black
#define my_search_half search_half_black
#define my_search_half_check search_half_check_black
#define my_exclude exclude_black
#define my_exclude_check exclude_check_black
#define my_node_cut node_cut_black
#define my_node_cut_check node_cut_check_black
#define my_node_total node_total_black
#define my_node_total_check node_total_check_black
#define my_node_pv node_pv_black
#define my_node_top node_top_black
#define my_high search_high_black
#define my_attack DYNAMIC->attak_black
#define your_attack DYNAMIC->attak_white
#define my_attack_pawn attack_pawn_black
#define your_attack_pawn attack_pawn_white
#define your_pv_search_fine pv_search_fine_white
#define your_pv_search_fine_check pv_search_fine_check_white
#define your_search_fine search_fine_white
#define your_search_fine_check search_fine_check_white
#define your_search_half search_half_white
#define your_search_half_check search_half_check_white
#define your_exclude exclude_white
#define your_exclude_check exclude_check_white
#define your_node_cut node_cut_white
#define your_node_cut_check node_cut_check_white
#define your_node_total node_total_white
#define your_node_total_check node_total_check_white
#define your_node_pv node_pv_white
#define your_node_top node_top_white
#define your_high search_high_white
#define your_occupied bitboard_occupied_white
#define bitboard_your_pawn bitboard_white_pawn
#define bitboard_your_knight bitboard_white_knight
#define bitboard_your_clear bitboard_white_clear
#define bitboard_your_dark bitboard_white_dark
#define bitboard_your_bishop (bitboard_your_clear|bitboard_your_dark)
#define bitboard_your_rook bitboard_white_rook
#define bitboard_your_queen bitboard_white_queen
#define bitboard_your_king bitboard_white_king
#define my_occupied bitboard_occupied_black
#define bitboard_my_pawn bitboard_black_pawn
#define bitboard_my_knight bitboard_black_knight
#define bitboard_my_clear bitboard_black_clear
#define bitboard_my_dark bitboard_black_dark
#define bitboard_my_bishop (bitboard_my_clear|bitboard_my_dark)
#define bitboard_my_rook bitboard_black_rook
#define bitboard_my_queen bitboard_black_queen
#define bitboard_my_king bitboard_black_king
#define my_square_king POSITION.black_king_square
#define your_square_king POSITION.white_king_square
#define count_your_pawn count_pawn_white
#define count_your_knight count_knight_white
#define count_your_clear count_clear_white
#define count_your_dark count_dark_white
#define count_your_rook count_rook_white
#define count_your_queen count_queen_white
#define count_your_king count_king_white
#define count_my_pawn count_pawn_black
#define count_my_knight count_knight_black
#define count_my_clear count_clear_black
#define count_my_dark count_dark_black
#define count_my_rook count_rook_black
#define count_my_queen count_queen_black
#define count_my_king count_king_black
#define your_king_check DYNAMIC->white_king_check
#define my_capture capture_black
#define my_ordinary ordinary_black
#define my_gain gain_black
#define my_evasion evasion_black
#define my_check_quiet check_quiet_black
#define my_see see_black
#define DO do_black
#define CANCEL cancel_black
#define move_illegal move_black_in_check
#define move_check move_white_in_check
#define my_ensure ensure_black
#define my_next next_black
#define my_null ((DYNAMIC->flags)&1)
#define RANK_SIX(x) ((x)<=H3)
#define RANK_FOUR(x) ((x)<=H5)
#define pawn_free pawn_free_black
#define my_xray (DYNAMIC->black_xray)
#define your_xray (DYNAMIC->white_xray)
#define my_xray_list xray_black_list
#define your_xray_list xray_white_list
#define my_king_check DYNAMIC->black_king_check
#define my_count count_black
#define my_count_flee count_black_flee
#define CHECK black_in_check

#define RANK_EIGHT(x) (x<=H1)
#define capture_straight ((bitboard_black_pawn&~FILEh)>>7)
#define di_left(x) (((x)+7)<<6)
#define capture_left ((bitboard_black_pawn&~FILEa)>>9)
#define di_straight(x) (((x)+9)<<6)
#define forward(x) ((x)-8)
#define forward_left(x) ((x)-9)
#define forward_straight(x) ((x)-7)
#define back(x) ((x)+8)
#define forward_turn(x) ((x)>>8)
#define back_turn(x) ((x)<<8)
#define RANK_SEVEN(x) (x<=H2)
#define back_turn_two(x) ((x)<<16)
#define forward_two(x) ((x)-16)
#define RANK_SECOND RANK7
#define en_rank_third(x) ((x&070)==050)
#define bitboard_rank_fourth RANK5
#define RANK_SECOND_SIX traversa37
#define bitboard_rank_seventh RANK2
#define bitboard_rank_eighth RANK1
#define WHITE_A7 A2
#define WHITE_H7 H2

#define capture_en_passant capture_value[count_pawn_black][count_pawn_white]
#define promotion_queen_capture ((0x28<<24)+capture_value[count_pawn_black][c])
#define promotion_knight_capture ((0x1a<<24)+capture_value[count_pawn_black][c])

#define castling_oo castling_black_oo
#define castling_ooo castling_black_ooo
#define WHITE_F1G1 F8G8
#define WHITE_C1D1 C8D8
#define WHITE_B1C1D1 B8C8D8
#define WHITE_E1 E8
#define WHITE_C1 C8
#define WHITE_G1 G8
#define under_promotion under_promotion_black

#define en_rank_second(x) ((x&070)==060)
#define straight_capture (((square_fixed[di]&nonH)>>7)&bitboard_occupied_white&cel)
#define left_capture (((square_fixed[di]&nonA)>>9)&bitboard_occupied_white&cel)
#define pawn_guardian(x,y) (DYNAMIC->attak_black&square_fixed[x] || ATTACK_file((y))&(bitboard_black_rook|bitboard_black_queen))
#define RANK_FOUR_EIGHT_noH (0x0000007f7f7f7f7f)
#define RANK_FOUR_EIGHT_noA (0x000000fefefefefe)
#define back_straight(x) ((x)+9)
#define back_straight_two(x) ((x)+17)
#define back_straight_three(x) ((x)+25)
#define back_left(x) ((x)+7)
#define back_left_two(x) ((x)+15)
#define back_left_three(x) ((x)+23)
#define number_rank5 T4

#define number_rank2 T7
#define my_piece PIECE_BLACK
#define your_piece PIECE_WHITE
#define back_two(x) ((x)+16)

#define your_pawn(x) ((x==count_pawn_white)?0xffffffffffffffff:0)
