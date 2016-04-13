/* ʱ������࣬��ͨ������һϵ�е�ʱ������ģ������Ч�� */

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

	// �ж���һ���ƶ���ʱ���Ƿ񵽴���
	// ������ControlEnd()Ϊ�棬�ܷ��ؼ�
	bool TimeTargetComplete();

	// �ж�ʱ�������Ƿ����
	bool ControlEnd();

	// ����ʱ�����н���
	void SetEnd();

	// ����ʱ������
	void Reset();

	// �������ظ����һ��ʱ��
	void ResetToLastInterval();

private:
	std::vector<clock_t> interval;
	std::vector<clock_t>::const_iterator ite;
	clock_t targetTime;
};