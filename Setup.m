%%
%  Find handle block name Serial Configuration
%  find_system(gcs,'FindAll','on','Name','Serial Configuration')
%
%% Serial Configuration
Port='COM9';
BaudRate= '500000';
DataBits='8';
Parity='none';
StopBits='1';
ByteOrder='little-endian';
FlowControl='none' ;
Timeout ='0.01';
%% Serial Send
Header='[]';
Terminator='<none>';
EnableBlockingMode='on';
%% Serial Receive
DataType='uint8'
ToggleHeader='off';
ToggleTerminator='off';
DataSize='[1 1]';
EnableBlockingMode='on';
ActionDataUnavailable='Output last received value';
SampleTime='0.01';
%%Serial Configuration
Serial_Configuration_Handle=find_system(gcs,'FindAll','on','Name','Serial Configuration')
% eg:1
% Serial_Configuration_Handle=find_system(gcs,'FindAll','on','Name','Serial Configuration')
%set_param(Serial_Configuration_Handle,'Port','COM10')
% eg:2
% Serial_Configuration_Handle=find_system(gcs,'Name','Serial Configuration')
%set_param(cell2mat(Serial_Configuration_Handle),'Port','COM10')

 %%Serial_Configuration_Handle = find_system(gcs,'Name','Serial Configuration')
% Individual encoders for each message to send
% for i = 1:length(messages_to_send)
%     filename = strcat(mavlink_path, '/mavlink_msg_', messages_to_send{i}, '.h');
%     create_sfun_encode(filename);
% end
Serial_Configuration_Handle=find_system(gcs,'FindAll','on','Name','Serial Configuration')
set_param(Serial_Configuration_Handle,'Port',Port)
set_param(Serial_Configuration_Handle,'BaudRate',BaudRate)
set_param(Serial_Configuration_Handle,'DataBits',DataBits)
set_param(Serial_Configuration_Handle,'Parity',Parity)
set_param(Serial_Configuration_Handle,'StopBits',StopBits)
set_param(Serial_Configuration_Handle,'ByteOrder',ByteOrder)
set_param(Serial_Configuration_Handle,'FlowControl',FlowControl)
set_param(Serial_Configuration_Handle,'Timeout',Timeout)

%% Serial Send
Serial_Send_Handle=find_system(gcs,'FindAll','on','Name','Serial Send')
set_param(Serial_Send_Handle,'Port',Port)
set_param(Serial_Send_Handle,'Header',Header)
set_param(Serial_Send_Handle,'Terminator',Terminator)
set_param(Serial_Send_Handle,'EnableBlockingMode',EnableBlockingMode)
%% Serial Receive
Serial_Receive_Handle=find_system(gcs,'FindAll','on','Name','Serial Receive')
set_param(Serial_Receive_Handle,'Port',Port)
set_param(Serial_Receive_Handle,'DataType',DataType)
set_param(Serial_Receive_Handle,'ToggleHeader',ToggleHeader)
set_param(Serial_Receive_Handle,'ToggleTerminator',ToggleTerminator)
set_param(Serial_Receive_Handle,'EnableBlockingMode',EnableBlockingMode)
set_param(Serial_Receive_Handle,'ActionDataUnavailable',ActionDataUnavailable)
set_param(Serial_Receive_Handle,'SampleTime',SampleTime)
