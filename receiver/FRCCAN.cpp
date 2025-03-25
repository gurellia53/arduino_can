#include "FRCCAN.h"

FRCCAN::FRCCAN(const tCAN &message) : m_message(message)
{
}

uint32_t FRCCAN::DeviceType() const
{
    return (m_message.id & 0b11111000000000000000000000000) >> 24;
}

uint32_t FRCCAN::Manufacturer() const
{
    return (m_message.id & 0b00000111111110000000000000000) >> 16;
}

uint32_t FRCCAN::MessageId() const
{
    return (m_message.id & 0b00000000000001111111111000000) >> 6;
}

uint32_t FRCCAN::APIClass() const
{
    return (m_message.id & 0b00000000000001111110000000000) >> 10;
}

uint32_t FRCCAN::APIIndex() const
{
    return (m_message.id & 0b00000000000000000001111000000) >> 6;
}

uint32_t FRCCAN::DeviceNumber() const
{
    return (m_message.id & 0b00000000000000000000000111111);
}

uint32_t FRCCAN::ID() const
{
    return m_message.id;
}
