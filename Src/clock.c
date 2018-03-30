/*
 * clock.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#include "clock.h"

uint8_t CLOCK_getTime(uint8_t* time) {

	uint8_t status = CLOCK_updateRTC();
	time[0] = current_time.Hours;
	time[1] = current_time.Minutes;
	time[2] = current_time.Seconds;
	return status;
}

uint8_t CLOCK_getDate(uint8_t* date) {

	uint8_t status = CLOCK_updateRTC();
	date[0] = current_date.Date;
	date[1] = current_date.Month;
	date[2] = current_date.Year;
	date[3] = current_date.WeekDay;
	return status;
}

uint8_t CLOCK_updateRTC(void) {

	uint8_t status = HAL_RTC_GetTime(&hrtc, &current_time, RTC_FORMAT_BIN);
	status += HAL_RTC_GetDate(&hrtc, &current_date, RTC_FORMAT_BIN);
	return status;
}

uint8_t CLOCK_setTime(uint8_t* time) {

	current_time.Hours = time[0];
	current_time.Minutes = time[1];
	current_time.Seconds = time[2];
	return HAL_RTC_SetTime(&hrtc, &current_time, RTC_FORMAT_BIN);
}

uint8_t CLOCK_setDate(uint8_t* date) {

	current_date.Date = date[0];
	current_date.Month = date[1];
	current_date.Year = date[2];
	current_date.WeekDay = date[3];
	return HAL_RTC_SetDate(&hrtc, &current_date, RTC_FORMAT_BIN);
}

uint8_t CLOCK_SetAlarm(uint8_t* time) {

	uint8_t data[50];
	uint8_t size = sprintf(data, "\nAlarm time: %d:%d:%d", time[0], time[1], time[2]);
	HAL_UART_Transmit_IT(&huart1, data, size);
	HAL_Delay(10);
	alarm_time.AlarmTime.Hours = time[0];
	alarm_time.AlarmTime.Minutes = time[1];
	alarm_time.AlarmTime.Seconds = time[2];
	alarm_time.AlarmTime.SubSeconds = 0x0;


	alarm_time.AlarmTime.TimeFormat = RTC_HOURFORMAT_24;
	alarm_time.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_None;
	alarm_time.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	alarm_time.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;


	alarm_time.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	alarm_time.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;


	alarm_time.AlarmDateWeekDay = RTC_WEEKDAY_FRIDAY;
	alarm_time.Alarm = RTC_ALARM_A;

	return HAL_RTC_SetAlarm_IT(&hrtc, &alarm_time, RTC_FORMAT_BIN);
}











