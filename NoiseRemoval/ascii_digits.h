//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Predefinisane vrednosti za ispis odredjenih karaktera na LCD ekran
// *
// *
//////////////////////////////////////////////////////////////////////////////


#ifndef DTMF_ASCII_DIGITS_H_
#define DTMF_ASCII_DIGITS_H_

const Int16 consolas_8ptBitmaps[] =
{
	/* @0 '#' (6 pixels wide) */
	//       
	//   # # 
	//   # # 
	// ######
	//   # # 
	// ######
	//  # #  
	//  # #  
	0x14, 0x17, 0x7C, 0x17, 0x7C, 0x14, 

	/* @6 '*' (6 pixels wide) */
	//    #  
	//  # # #
	//   ### 
	//  # # #
	//    #  
	//       
	//       
	//       
	0x00, 0x50, 0x20, 0xF8, 0x20, 0x50, 

	/* @12 '0' (6 pixels wide) */
	//       
	//  ###  
	// #   # 
	// #  ## 
	// # # # 
	// ##  # 
	// #   # 
	//  ###  
	0x3E, 0x45, 0x49, 0x51, 0x3E, 0x00, 

	/* @18 '1' (6 pixels wide) */
	//       
	//   ##  
	//  # #  
	//    #  
	//    #  
	//    #  
	//    #  
	//  #####
	0x00, 0x21, 0x41, 0x7F, 0x01, 0x01, 

	/* @24 '2' (6 pixels wide) */
	//       
	//   ### 
	//  #   #
	//      #
	//     # 
	//    #  
	//   #   
	//  #####
	0x00, 0x21, 0x43, 0x45, 0x49, 0x31, 

	/* @30 '3' (6 pixels wide) */
	//       
	//  ###  
	//     # 
	//     # 
	//   ##  
	//     # 
	//     # 
	//  ###  
	0x00, 0x41, 0x49, 0x49, 0x36, 0x00, 

	/* @36 '4' (6 pixels wide) */
	//       
	//    ## 
	//   # # 
	//  #  # 
	// #   # 
	// ######
	//     # 
	//     # 
	0x0C, 0x14, 0x24, 0x44, 0x7F, 0x04, 

	/* @42 '5' (6 pixels wide) */
	//       
	//  #### 
	//  #    
	//  #    
	//  ###  
	//     # 
	//     # 
	//  ###  
	0x00, 0x79, 0x49, 0x49, 0x46, 0x00, 

	/* @48 '6' (6 pixels wide) */
	//       
	//   ### 
	//  ##   
	//  #    
	//  #### 
	//  #   #
	//  #   #
	//   ### 
	0x00, 0x3E, 0x69, 0x49, 0x49, 0x06, 

	/* @54 '7' (6 pixels wide) */
	//       
	//  #####
	//      #
	//     # 
	//     # 
	//    #  
	//    #  
	//   #   
	0x00, 0x40, 0x41, 0x46, 0x58, 0x60, 

	/* @60 '8' (6 pixels wide) */
	//       
	//   ### 
	//  #   #
	//  ##  #
	//   ### 
	//  #  ##
	//  #   #
	//   ### 
	0x00, 0x36, 0x59, 0x49, 0x4D, 0x36, 

	/* @66 '9' (6 pixels wide) */
	//       
	//   ### 
	//  #   #
	//  #   #
	//   ####
	//      #
	//     # 
	//  ###  
	0x00, 0x31, 0x49, 0x49, 0x4A, 0x3C, 

	/* @72 'A' (6 pixels wide) */
	//       
	//    #  
	//   # # 
	//   # # 
	//   # # 
	//  #####
	//  #   #
	//  #   #
	0x00, 0x07, 0x3C, 0x44, 0x3C, 0x07, 

	/* @78 'B' (6 pixels wide) */
	//       
	//  #### 
	//  #   #
	//  #   #
	//  #### 
	//  #   #
	//  #   #
	//  #### 
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 

	/* @84 'C' (6 pixels wide) */
	//       
	//   ### 
	//  ##   
	//  #    
	//  #    
	//  #    
	//  ##   
	//   ### 
	0x00, 0x3E, 0x63, 0x41, 0x41, 0x00, 

	/* @90 'D' (6 pixels wide) */
	//       
	//  #### 
	//  #  ##
	//  #   #
	//  #   #
	//  #   #
	//  #  ##
	//  #### 
	0x00, 0x7F, 0x41, 0x41, 0x63, 0x3E, 
};

const Int16 sign_width = 6;

#endif /* DTMF_ASCII_DIGITS_H_ */
