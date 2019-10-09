clc;
clear all;
close all;

delete(instrfindall);
instrhwinfo('Bluetooth','HC-05');
arduino = Bluetooth('HC-05',1);
fopen(arduino);

data_att = zeros(1,256);
data_blink = zeros(1,256);

portnum1 = 3;
comPortName1 = sprintf('\\\\.\\COM%d', portnum1);

TG_BAUD_115200 = 115200;

TG_STREAM_PACKETS = 0;

TG_DATA_ATTENTION = 2;
TG_DATA_BLINK_STRENGTH = 37;

loadlibrary('Thinkgear.dll');

fprintf('Thinkgear.dll loaded\n');

dllVersion = calllib('Thinkgear', 'TG_GetDriverVersion');

fprintf('ThinkGear DLL version: %d\n', dllVersion );

connectionId1 = calllib('Thinkgear', 'TG_GetNewConnectionId');
if ( connectionId1 < 0 )
    error( sprintf( 'ERROR: TG_GetNewConnectionId() returned %d.\n',...
        connectionId1 ) );
end;

errCode = calllib('Thinkgear', 'TG_Connect', connectionId1, ...
    comPortName1,TG_BAUD_115200,TG_STREAM_PACKETS );
if ( errCode < 0 )
    error( sprintf( 'ERROR: TG_Connect() returned %d.\n', errCode ) );
end

fprintf( 'Connected.  Reading Packets...\n' );

if(calllib('Thinkgear','TG_EnableBlinkDetection',connectionId1,1)==0)
    disp('blinkdetectenabled');
end

j=0;
l=0;

disp('Reading Brainwaves');


while true
    if (calllib('Thinkgear','TG_ReadPackets',connectionId1,1) == 1)               
         if ((calllib('Thinkgear','TG_GetValueStatus',...
                connectionId1,TG_DATA_ATTENTION)~= 0))

            j = j + 1;
            data_att(j) = calllib('Thinkgear','TG_GetValue', ...
                connectionId1,TG_DATA_ATTENTION);
            att = floor(data_att(j)/25)
            H1 = num2str(att);
            fprintf(arduino,char(H1));

            figure(01);
            plot(data_att);
            title('Attention');
            
            pause(0.0001);
         end
        
        if ((calllib('Thinkgear','TG_GetValueStatus',...
                connectionId1,TG_DATA_BLINK_STRENGTH)~= 0))
            l = l + 1;
            data_blink(l) = calllib('Thinkgear','TG_GetValue', ...
                connectionId1,TG_DATA_BLINK_STRENGTH );
            data_blink(l) = data_blink(l) + 200;
            blink = floor((data_blink(l)/50)+1)
            H2 = num2str(blink);
            fprintf(arduino,char(H2));
            figure(02);
            plot(data_blink);
            title('EyeBlink');
        end
    end
end

disp('Loop Completed');
fclose(arduino);
calllib('Thinkgear', 'TG_FreeConnection', connectionId1 );