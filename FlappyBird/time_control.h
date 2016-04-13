/* 时间管理类，可通过输入一系列的时间间隔来模拟重力效果 */

#pragma once

#include <ctime>
#include <vector>

class TimeControl
{
public:
	TimeControl() = delete;
	TimeControl(const std::vector<clock_t>& i);
	TimeControl(std::vector<clock_t>&& i);
	TimeControl(const TimeControl&) = default;
	TimeControl(TimeControl&&) = default;
	TimeControl& operator= (const TimeControl&) = default;
	TimeControl& operator= (TimeControl&&) = default;

	// 判断下一次移动的时间是否到达了
	// 并且若ControlEnd()为真，总返回假
	bool TimeTargetComplete();

	// 判断时间序列是否结束
	bool ControlEnd();

	// 设置时间序列结束
	void SetEnd();

	// 重置时间序列
	void Reset();

	// 可用来重复最后一个时间
	void ResetToLastInterval();

private:
	std::vector<clock_t> interval;
	std::vector<clock_t>::const_iterator ite;
	clock_t targetTime;
};