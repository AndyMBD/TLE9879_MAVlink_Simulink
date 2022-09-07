#pragma once
// MESSAGE PMSM_Command PACKING

#define MAVLINK_MSG_ID_PMSM_Command 1


typedef struct __mavlink_pmsm_command_t {
 char Direction; /*<  Motor Direction*/
 uint8_t Speed; /*<  Motor Speed*/
} mavlink_pmsm_command_t;

#define MAVLINK_MSG_ID_PMSM_Command_LEN 2
#define MAVLINK_MSG_ID_PMSM_Command_MIN_LEN 2
#define MAVLINK_MSG_ID_1_LEN 2
#define MAVLINK_MSG_ID_1_MIN_LEN 2

#define MAVLINK_MSG_ID_PMSM_Command_CRC 8
#define MAVLINK_MSG_ID_1_CRC 8



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PMSM_Command { \
    1, \
    "PMSM_Command", \
    2, \
    {  { "Direction", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_pmsm_command_t, Direction) }, \
         { "Speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_pmsm_command_t, Speed) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PMSM_Command { \
    "PMSM_Command", \
    2, \
    {  { "Direction", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_pmsm_command_t, Direction) }, \
         { "Speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_pmsm_command_t, Speed) }, \
         } \
}
#endif

/**
 * @brief Pack a pmsm_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Direction  Motor Direction
 * @param Speed  Motor Speed
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsm_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               char Direction, uint8_t Speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Command_LEN];
    _mav_put_char(buf, 0, Direction);
    _mav_put_uint8_t(buf, 1, Speed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PMSM_Command_LEN);
#else
    mavlink_pmsm_command_t packet;
    packet.Direction = Direction;
    packet.Speed = Speed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PMSM_Command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PMSM_Command;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
}

/**
 * @brief Pack a pmsm_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Direction  Motor Direction
 * @param Speed  Motor Speed
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsm_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   char Direction,uint8_t Speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Command_LEN];
    _mav_put_char(buf, 0, Direction);
    _mav_put_uint8_t(buf, 1, Speed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PMSM_Command_LEN);
#else
    mavlink_pmsm_command_t packet;
    packet.Direction = Direction;
    packet.Speed = Speed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PMSM_Command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PMSM_Command;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
}

/**
 * @brief Encode a pmsm_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pmsm_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsm_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pmsm_command_t* pmsm_command)
{
    return mavlink_msg_pmsm_command_pack(system_id, component_id, msg, pmsm_command->Direction, pmsm_command->Speed);
}

/**
 * @brief Encode a pmsm_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pmsm_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsm_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pmsm_command_t* pmsm_command)
{
    return mavlink_msg_pmsm_command_pack_chan(system_id, component_id, chan, msg, pmsm_command->Direction, pmsm_command->Speed);
}

/**
 * @brief Send a pmsm_command message
 * @param chan MAVLink channel to send the message
 *
 * @param Direction  Motor Direction
 * @param Speed  Motor Speed
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pmsm_command_send(mavlink_channel_t chan, char Direction, uint8_t Speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PMSM_Command_LEN];
    _mav_put_char(buf, 0, Direction);
    _mav_put_uint8_t(buf, 1, Speed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Command, buf, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
#else
    mavlink_pmsm_command_t packet;
    packet.Direction = Direction;
    packet.Speed = Speed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Command, (const char *)&packet, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
#endif
}

/**
 * @brief Send a pmsm_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pmsm_command_send_struct(mavlink_channel_t chan, const mavlink_pmsm_command_t* pmsm_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pmsm_command_send(chan, pmsm_command->Direction, pmsm_command->Speed);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Command, (const char *)pmsm_command, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
#endif
}

#if MAVLINK_MSG_ID_PMSM_Command_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pmsm_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  char Direction, uint8_t Speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_char(buf, 0, Direction);
    _mav_put_uint8_t(buf, 1, Speed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Command, buf, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
#else
    mavlink_pmsm_command_t *packet = (mavlink_pmsm_command_t *)msgbuf;
    packet->Direction = Direction;
    packet->Speed = Speed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PMSM_Command, (const char *)packet, MAVLINK_MSG_ID_PMSM_Command_MIN_LEN, MAVLINK_MSG_ID_PMSM_Command_LEN, MAVLINK_MSG_ID_PMSM_Command_CRC);
#endif
}
#endif

#endif

// MESSAGE PMSM_Command UNPACKING


/**
 * @brief Get field Direction from pmsm_command message
 *
 * @return  Motor Direction
 */
static inline char mavlink_msg_pmsm_command_get_Direction(const mavlink_message_t* msg)
{
    return _MAV_RETURN_char(msg,  0);
}

/**
 * @brief Get field Speed from pmsm_command message
 *
 * @return  Motor Speed
 */
static inline uint8_t mavlink_msg_pmsm_command_get_Speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a pmsm_command message into a struct
 *
 * @param msg The message to decode
 * @param pmsm_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_pmsm_command_decode(const mavlink_message_t* msg, mavlink_pmsm_command_t* pmsm_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pmsm_command->Direction = mavlink_msg_pmsm_command_get_Direction(msg);
    pmsm_command->Speed = mavlink_msg_pmsm_command_get_Speed(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PMSM_Command_LEN? msg->len : MAVLINK_MSG_ID_PMSM_Command_LEN;
        memset(pmsm_command, 0, MAVLINK_MSG_ID_PMSM_Command_LEN);
    memcpy(pmsm_command, _MAV_PAYLOAD(msg), len);
#endif
}
