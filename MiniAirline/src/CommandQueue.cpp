#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	m_Queue.push(command);
}

Command CommandQueue::pop()
{
	Command command = m_Queue.front();
	m_Queue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return m_Queue.empty();
}
