#include "FRCCAN.h"

namespace
{
    constexpr uint32_t DEVICE_TYPE_MASK = 0b11111000000000000000000000000;
    constexpr uint32_t MANUFACTURER_MASK = 0b00000111111110000000000000000;
    constexpr uint32_t MESSAGE_ID_MASK = 0b00000000000001111111111000000;
    constexpr uint32_t API_CLASS_MASK = 0b00000000000001111110000000000;
    constexpr uint32_t API_INDEX_MASK = 0b00000000000000000001111000000;
    constexpr uint32_t DEVICE_NUMBER_MASK = 0b00000000000000000000000111111;
}

FRCCAN::FRCCAN(const tCAN &message) : m_message(message)
{
}

FRCCAN::FRCCAN(uint32_t device_type,
               uint32_t manufacturer,
               uint32_t api_class,
               uint32_t api_index,
               uint32_t device_number)
{
    m_message.id = 0x00000000;
    m_message.id |= (device_type << 24) & DEVICE_TYPE_MASK;
    m_message.id |= (manufacturer << 16) & MANUFACTURER_MASK;
    m_message.id |= (api_class << 10) & API_CLASS_MASK;
    m_message.id |= (api_index << 6) & API_INDEX_MASK;
    m_message.id |= device_number & DEVICE_NUMBER_MASK;
}

tCAN *FRCCAN::Get()
{
    return &m_message;
}

uint32_t FRCCAN::DeviceType() const
{
    return (m_message.id & DEVICE_TYPE_MASK) >> 24;
}

uint32_t FRCCAN::Manufacturer() const
{
    return (m_message.id & MANUFACTURER_MASK) >> 16;
}

uint32_t FRCCAN::MessageId() const
{
    return (m_message.id & MESSAGE_ID_MASK) >> 6;
}

uint32_t FRCCAN::APIClass() const
{
    return (m_message.id & API_CLASS_MASK) >> 10;
}

uint32_t FRCCAN::APIIndex() const
{
    return (m_message.id & API_INDEX_MASK) >> 6;
}

uint32_t FRCCAN::DeviceNumber() const
{
    return (m_message.id & DEVICE_NUMBER_MASK);
}

uint32_t FRCCAN::ID() const
{
    return m_message.id;
}
