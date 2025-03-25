#pragma once
#include <Canbus.h>
#include <mcp2515.h>

class FRCCAN : public tCAN
{
public:
    FRCCAN(const tCAN &message);

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
