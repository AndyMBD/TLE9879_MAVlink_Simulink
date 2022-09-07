/** @file
 *    @brief MAVLink comm protocol testsuite generated from TLE9879_MAVlink.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef TLE9879_MAVLINK_TESTSUITE_H
#define TLE9879_MAVLINK_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_TLE9879_MAVlink(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_TLE9879_MAVlink(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_pmsm_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PMSM_Status >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_pmsm_status_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,77
    };
    mavlink_pmsm_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Battery_Voltage = packet_in.Battery_Voltage;
        packet1.Phase_Current_U = packet_in.Phase_Current_U;
        packet1.Phase_Current_V = packet_in.Phase_Current_V;
        packet1.Phase_Current_W = packet_in.Phase_Current_W;
        packet1.T1 = packet_in.T1;
        packet1.T2 = packet_in.T2;
        packet1.Sector = packet_in.Sector;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PMSM_Status_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PMSM_Status_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_pmsm_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_status_pack(system_id, component_id, &msg , packet1.Battery_Voltage , packet1.Phase_Current_U , packet1.Phase_Current_V , packet1.Phase_Current_W , packet1.T1 , packet1.T2 , packet1.Sector );
    mavlink_msg_pmsm_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Battery_Voltage , packet1.Phase_Current_U , packet1.Phase_Current_V , packet1.Phase_Current_W , packet1.T1 , packet1.T2 , packet1.Sector );
    mavlink_msg_pmsm_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_pmsm_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_status_send(MAVLINK_COMM_1 , packet1.Battery_Voltage , packet1.Phase_Current_U , packet1.Phase_Current_V , packet1.Phase_Current_W , packet1.T1 , packet1.T2 , packet1.Sector );
    mavlink_msg_pmsm_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PMSM_Status") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PMSM_Status) != NULL);
#endif
}

static void mavlink_test_pmsm_command(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PMSM_Command >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_pmsm_command_t packet_in = {
        'A',72
    };
    mavlink_pmsm_command_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Direction = packet_in.Direction;
        packet1.Speed = packet_in.Speed;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PMSM_Command_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PMSM_Command_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_command_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_pmsm_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_command_pack(system_id, component_id, &msg , packet1.Direction , packet1.Speed );
    mavlink_msg_pmsm_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_command_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Direction , packet1.Speed );
    mavlink_msg_pmsm_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_pmsm_command_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsm_command_send(MAVLINK_COMM_1 , packet1.Direction , packet1.Speed );
    mavlink_msg_pmsm_command_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PMSM_Command") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PMSM_Command) != NULL);
#endif
}

static void mavlink_test_TLE9879_MAVlink(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_pmsm_status(system_id, component_id, last_msg);
    mavlink_test_pmsm_command(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // TLE9879_MAVLINK_TESTSUITE_H
