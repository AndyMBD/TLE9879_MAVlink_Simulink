#pragma once
// MESSAGE PMSM_Status PACKING

#define MAVLINK_MSG_ID_PMSM_Status 0


typedef struct __mavlink_pmsm_status_t {
 float Battery_Voltage; /*<  Battery Voltage*/
 float Phase_Current_U; /*<  Phase current U*/
 float Phase_Current_V; /*<  Phase current V*/
 float Phase_Current_W; /*<  Phase current W*/
 float T1; /*<  SVPWM T1*/
 float T2; /*<  SVPWM T2*/
 uint8_t Sector; /*<  SVPWM Sector*/
} mavlink_pmsm_status_t;

#define MAVLINK_MSG_ID_PMSM_Status_LEN 25
#define MAVLINK_MSG_ID_PMSM_Status_MIN_LEN 25
#define MAVLINK_MSG_ID_0_LEN 25
#define MAVLINK_MSG_ID_0_MIN_LEN 25

#define MAVLINK_MSG_ID_PMSM_Status_CRC 83
#define MAVLINK_MSG_ID_0_CRC 83



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PMSM_Status { \
    0, \
    "PMSM_Status", \
    7, \
    {  { "Battery_Voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pmsm_status_t, Battery_Voltage) }, \
         { "Phase_Current_U", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pmsm_status_t, Phase_Current_U) }, \
         { "Phase_Current_V", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pmsm_status_t, Phase_Current_V) }, \
         { "Phase_Current_W", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pmsm_status_t, Phase_Current_W) }, \
         { "T1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pmsm_status_t, T1) }, \
         { "T2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pmsm_status_t, T2) }, \
         { "Sector", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_pmsm_status_t, Sector) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PMSM_Status { \
    "PMSM_Status", \
    7, \
    {  { "Battery_Voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pmsm_status_t, Battery_Voltage) }, \
         { "Phase_Current_U", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pmsm_status_t, Phase_Current_U) }, \
         { "Phase_Current_V", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pmsm_status_t, Phase_Current_V) }, \
         { "Phase_Current_W", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pmsm_status_t, Phase_Current_W) }, \
         { "T1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pmsm_status_t, T1) }, \
         { "T2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pmsm_status_t, T2) }, \
         { "Sector", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_pmsm_status_t, Sector) }, \
         } \
}
#endif

/**
 * @brief Pack a pmsm_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Battery_Voltage  Battery Voltage
 * @param Phase_Current_U  Phase current U
 * @param Phase_Current_V  Phase current V
 * @param Phase_Current_W  Phase current W
 * @param T1  SVPWM T1
 * @param T2  SVPWM T2
 * @param Sector  SVPWM Sector
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsm_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float Battery_Voltage, float Phase_Current_U, float Phase_Current_V, float Phase_Current_W, float T1, float T2, uint8_t Sector)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Status_LEN];
    _mav_put_float(buf, 0, Battery_Voltage);
    _mav_put_float(buf, 4, Phase_Current_U);
    _mav_put_float(buf, 8, Phase_Current_V);
    _mav_put_float(buf, 12, Phase_Current_W);
    _mav_put_float(buf, 16, T1);
    _mav_put_float(buf, 20, T2);
    _mav_put_uint8_t(buf, 24, Sector);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PMSM_Status_LEN);
#else
    mavlink_pmsm_status_t packet;
    packet.Battery_Voltage = Battery_Voltage;
    packet.Phase_Current_U = Phase_Current_U;
    packet.Phase_Current_V = Phase_Current_V;
    packet.Phase_Current_W = Phase_Current_W;
    packet.T1 = T1;
    packet.T2 = T2;
    packet.Sector = Sector;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PMSM_Status_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PMSM_Status;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
}

/**
 * @brief Pack a pmsm_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Battery_Voltage  Battery Voltage
 * @param Phase_Current_U  Phase current U
 * @param Phase_Current_V  Phase current V
 * @param Phase_Current_W  Phase current W
 * @param T1  SVPWM T1
 * @param T2  SVPWM T2
 * @param Sector  SVPWM Sector
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsm_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float Battery_Voltage,float Phase_Current_U,float Phase_Current_V,float Phase_Current_W,float T1,float T2,uint8_t Sector)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Status_LEN];
    _mav_put_float(buf, 0, Battery_Voltage);
    _mav_put_float(buf, 4, Phase_Current_U);
    _mav_put_float(buf, 8, Phase_Current_V);
    _mav_put_float(buf, 12, Phase_Current_W);
    _mav_put_float(buf, 16, T1);
    _mav_put_float(buf, 20, T2);
    _mav_put_uint8_t(buf, 24, Sector);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PMSM_Status_LEN);
#else
    mavlink_pmsm_status_t packet;
    packet.Battery_Voltage = Battery_Voltage;
    packet.Phase_Current_U = Phase_Current_U;
    packet.Phase_Current_V = Phase_Current_V;
    packet.Phase_Current_W = Phase_Current_W;
    packet.T1 = T1;
    packet.T2 = T2;
    packet.Sector = Sector;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PMSM_Status_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PMSM_Status;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
}

/**
 * @brief Encode a pmsm_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pmsm_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsm_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pmsm_status_t* pmsm_status)
{
    return mavlink_msg_pmsm_status_pack(system_id, component_id, msg, pmsm_status->Battery_Voltage, pmsm_status->Phase_Current_U, pmsm_status->Phase_Current_V, pmsm_status->Phase_Current_W, pmsm_status->T1, pmsm_status->T2, pmsm_status->Sector);
}

/**
 * @brief Encode a pmsm_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pmsm_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsm_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pmsm_status_t* pmsm_status)
{
    return mavlink_msg_pmsm_status_pack_chan(system_id, component_id, chan, msg, pmsm_status->Battery_Voltage, pmsm_status->Phase_Current_U, pmsm_status->Phase_Current_V, pmsm_status->Phase_Current_W, pmsm_status->T1, pmsm_status->T2, pmsm_status->Sector);
}

/**
 * @brief Send a pmsm_status message
 * @param chan MAVLink channel to send the message
 *
 * @param Battery_Voltage  Battery Voltage
 * @param Phase_Current_U  Phase current U
 * @param Phase_Current_V  Phase current V
 * @param Phase_Current_W  Phase current W
 * @param T1  SVPWM T1
 * @param T2  SVPWM T2
 * @param Sector  SVPWM Sector
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pmsm_status_send(mavlink_channel_t chan, float Battery_Voltage, float Phase_Current_U, float Phase_Current_V, float Phase_Current_W, float T1, float T2, uint8_t Sector)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Status_LEN];
    _mav_put_float(buf, 0, Battery_Voltage);
    _mav_put_float(buf, 4, Phase_Current_U);
    _mav_put_float(buf, 8, Phase_Current_V);
    _mav_put_float(buf, 12, Phase_Current_W);
    _mav_put_float(buf, 16, T1);
    _mav_put_float(buf, 20, T2);
    _mav_put_uint8_t(buf, 24, Sector);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Status, buf, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
#else
    mavlink_pmsm_status_t packet;
    packet.Battery_Voltage = Battery_Voltage;
    packet.Phase_Current_U = Phase_Current_U;
    packet.Phase_Current_V = Phase_Current_V;
    packet.Phase_Current_W = Phase_Current_W;
    packet.T1 = T1;
    packet.T2 = T2;
    packet.Sector = Sector;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Status, (const char *)&packet, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
#endif
}

/**
 * @brief Send a pmsm_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pmsm_status_send_struct(mavlink_channel_t chan, const mavlink_pmsm_status_t* pmsm_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pmsm_status_send(chan, pmsm_status->Battery_Voltage, pmsm_status->Phase_Current_U, pmsm_status->Phase_Current_V, pmsm_status->Phase_Current_W, pmsm_status->T1, pmsm_status->T2, pmsm_status->Sector);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Status, (const char *)pmsm_status, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
#endif
}

#if MAVLINK_MSG_ID_PMSM_Status_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pmsm_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float Battery_Voltage, float Phase_Current_U, float Phase_Current_V, float Phase_Current_W, float T1, float T2, uint8_t Sector)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, Battery_Voltage);
    _mav_put_float(buf, 4, Phase_Current_U);
    _mav_put_float(buf, 8, Phase_Current_V);
    _mav_put_float(buf, 12, Phase_Current_W);
    _mav_put_float(buf, 16, T1);
    _mav_put_float(buf, 20, T2);
    _mav_put_uint8_t(buf, 24, Sector);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Status, buf, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
#else
    mavlink_pmsm_status_t *packet = (mavlink_pmsm_status_t *)msgbuf;
    packet->Battery_Voltage = Battery_Voltage;
    packet->Phase_Current_U = Phase_Current_U;
    packet->Phase_Current_V = Phase_Current_V;
    packet->Phase_Current_W = Phase_Current_W;
    packet->T1 = T1;
    packet->T2 = T2;
    packet->Sector = Sector;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Status, (const char *)packet, MAVLINK_MSG_ID_PMSM_Status_MIN_LEN, MAVLINK_MSG_ID_PMSM_Status_LEN, MAVLINK_MSG_ID_PMSM_Status_CRC);
#endif
}
#endif

#endif

// MESSAGE PMSM_Status UNPACKING


/**
 * @brief Get field Battery_Voltage from pmsm_status message
 *
 * @return  Battery Voltage
 */
static inline float mavlink_msg_pmsm_status_get_Battery_Voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field Phase_Current_U from pmsm_status message
 *
 * @return  Phase current U
 */
static inline float mavlink_msg_pmsm_status_get_Phase_Current_U(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field Phase_Current_V from pmsm_status message
 *
 * @return  Phase current V
 */
static inline float mavlink_msg_pmsm_status_get_Phase_Current_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Phase_Current_W from pmsm_status message
 *
 * @return  Phase current W
 */
static inline float mavlink_msg_pmsm_status_get_Phase_Current_W(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field T1 from pmsm_status message
 *
 * @return  SVPWM T1
 */
static inline float mavlink_msg_pmsm_status_get_T1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field T2 from pmsm_status message
 *
 * @return  SVPWM T2
 */
static inline float mavlink_msg_pmsm_status_get_T2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field Sector from pmsm_status message
 *
 * @return  SVPWM Sector
 */
static inline uint8_t mavlink_msg_pmsm_status_get_Sector(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Decode a pmsm_status message into a struct
 *
 * @param msg The message to decode
 * @param pmsm_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_pmsm_status_decode(const mavlink_message_t* msg, mavlink_pmsm_status_t* pmsm_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pmsm_status->Battery_Voltage = mavlink_msg_pmsm_status_get_Battery_Voltage(msg);
    pmsm_status->Phase_Current_U = mavlink_msg_pmsm_status_get_Phase_Current_U(msg);
    pmsm_status->Phase_Current_V = mavlink_msg_pmsm_status_get_Phase_Current_V(msg);
    pmsm_status->Phase_Current_W = mavlink_msg_pmsm_status_get_Phase_Current_W(msg);
    pmsm_status->T1 = mavlink_msg_pmsm_status_get_T1(msg);
    pmsm_status->T2 = mavlink_msg_pmsm_status_get_T2(msg);
    pmsm_status->Sector = mavlink_msg_pmsm_status_get_Sector(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PMSM_Status_LEN? msg->len : MAVLINK_MSG_ID_PMSM_Status_LEN;
        memset(pmsm_status, 0, MAVLINK_MSG_ID_PMSM_Status_LEN);
    memcpy(pmsm_status, _MAV_PAYLOAD(msg), len);
#endif
}
