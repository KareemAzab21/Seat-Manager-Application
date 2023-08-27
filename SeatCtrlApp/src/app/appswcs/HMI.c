/**
 *
 * \file HMI_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: HMI
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 4/28/2023 07:09 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_HMI.h"

/**
 *
 * Runnable HMI_MainFunction
 *
 * Triggered By:
 *  - TimingEventImpl.TE_HMI_MainFunction_100ms
 *
 */

void HMI_MainFunction(void)
{
	Std_ReturnType status;
	MultiStateBtnType HeightBtnState;
	MultiStateBtnType InclineBtnState;
	MultiStateBtnType SlideBtnState;
	uint8 Height;
	uint8 Incline;
	uint8 Slide;
	/* Data Receive Points */

	status = Rte_Read_rpSeatCtrlData_Height(&Height);

	if (Height == 0 )
	{
		HeightBtnState = MULTI_STATE_BTN_INIT;
	}
	else if (Height == 1)
	{
		HeightBtnState = MULTI_STATE_BTN_MINUS;
	}
	else if (Height == 2)
	{
		HeightBtnState = MULTI_STATE_BTN_PLUS;
	}
	else
	{
		/*Report Error*/
	}

	status = Rte_Read_rpSeatCtrlData_Incline(&Incline);

	if (Incline == 0 )
	{
		InclineBtnState = MULTI_STATE_BTN_INIT;
	}
	else if (Incline == 1)
	{
		InclineBtnState = MULTI_STATE_BTN_MINUS;
	}
	else if (Incline == 2)
	{
		InclineBtnState = MULTI_STATE_BTN_PLUS;
	}
	else
	{
		/*Report Error*/
	}

	status = Rte_Read_rpSeatCtrlData_Slide(&Slide);

	if (Slide == 0 )
	{
		SlideBtnState = MULTI_STATE_BTN_INIT;
	}
	else if (Slide == 1)
	{
		SlideBtnState = MULTI_STATE_BTN_MINUS;
	}
	else if (Slide == 2)
	{
		SlideBtnState = MULTI_STATE_BTN_PLUS;
	}
	else
	{
		/*Report Error*/
	}

	/* Data Send Points */
	(void)Rte_Write_ppSeatCtrlBtns_HeightBtnState(HeightBtnState);
	(void)Rte_Write_ppSeatCtrlBtns_InclineBtnState(InclineBtnState);
	(void)Rte_Write_ppSeatCtrlBtns_SlideBtnState(SlideBtnState);
}

/**
 *
 * Runnable HMI_SeatModeChanged
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpSeatModeBtn_SeatModeBtn
 *
 */

void HMI_SeatModeChanged(void)
{
	Std_ReturnType status;
	SeatModeBtnType SeatModeBtn;
	uint8 SeatCtrlMode = RTE_MODE_SeatCtrlMode_INIT;

	/* Data Receive Points */
	(void)Rte_Read_rpSeatModeBtn_SeatModeBtn(&SeatModeBtn);
	if (SeatModeBtn == SEAT_MODE_BTN_MANUAL)
	{
		SeatCtrlMode = RTE_MODE_SeatCtrlMode_MANUAL;
	}
	else if (SeatModeBtn == SEAT_MODE_BTN_AUTO)
	{
		SeatCtrlMode = RTE_MODE_SeatCtrlMode_AUTO;
	}
	else
	{
		// report error
	}

	status = Rte_Switch_ppSeatCtrlMode_SeatCtrlMode(SeatCtrlMode);
}

static MultiStateBtnType btnValueToState(uint8 value)
{
	MultiStateBtnType btnState;
	
	if(value == 1)
	{
		btnState = MULTI_STATE_BTN_MINUS;
	}
	else if(value == 2)
	{
		btnState = MULTI_STATE_BTN_PLUS;
	}
	else
	{
		btnState = MULTI_STATE_BTN_INIT;
	}
	
	return btnState;
}