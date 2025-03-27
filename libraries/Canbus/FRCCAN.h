#pragma once
#include <Canbus.h>
#include <mcp2515.h>

class FRCCAN : public tCAN
{
public:
    FRCCAN(const tCAN &message);

    FRCCAN(uint32_t device_type,
           uint32_t manufacturer,
           uint32_t api_class,
           uint32_t api_index,
           uint32_t device_number);

    tCAN *Get();

    uint32_t DeviceType() const;
    uint32_t Manufacturer() const;
    uint32_t MessageId() const;
    uint32_t APIClass() const;
    uint32_t APIIndex() const;
    uint32_t DeviceNumber() const;

    uint32_t ID() const;

private:
    tCAN m_message;
};
