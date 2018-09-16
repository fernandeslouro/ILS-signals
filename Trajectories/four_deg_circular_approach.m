lon_start = 38.733817;
lat_start = -9.214631;
alt_start = 550;

lon_md = 38.707348;
lat_md =  -9.209038;
alt_md = 480;

lon_7 = 38.7185;
lat_7 = -9.169229;
alt_7 = tan(4*pi/180)*7000;
close all

x = [0  225 450];
y = [lon_start  lon_md lon_7];
p = polyfit(x,y,2)
x1 = 0:450;
y1 = polyval(p, x1);
plot(x,y,'o',x1,y1);
hold on;

x = [0  225 450];
y = [lat_start  lat_md lat_7];
p = polyfit(x,y,2)
x2 = 0:450;
y2 = polyval(p, x1);
plot(x,y,'o',x2,y2);
hold on;

lon_aero = 38.77559;
lat_aero = -9.13536;
alt_aero = 0;

len_data = 1800;
len_md = 250;
len_7 = 450;

lon = 0:len_data;
lat = 0:len_data;
alt = 0:len_data;
x = 0:len_data;
dist = 0:len_data;

pitch = 0:len_data;
roll = 0:len_data;
yaw = 0:len_data;

for k = 1:len_data+1
    if (k <= len_7)
        lon(k) = y1(k);
        lat(k) = y2(k);
        alt(k) = alt_start+(alt_7-alt_start)/(len_7)*k;
        
        pitch(k) = 8;
        roll(k) = -10;
        yaw(k) = 25+120-120*k/450;
        
        if k > 250
            roll(k) =  -10 + 10*(k-250)/200 ;
        end
        if k > 300
            pitch(k) =  8 - 3*(k-300)/150 ;
        end
    else
        lon(k) = lon_7+(lon_aero-lon_7)/(len_data-len_7)*(k-len_7-1);
        lat(k) = lat_7+(lat_aero-lat_7)/(len_data-len_7)*(k-len_7-1);
        alt(k) = alt_7+(alt_aero-alt_7)/(len_data-len_7)*(k-len_7-1);
        
         pitch(k) = 5;
         roll(k) = 0;
         yaw(k) = 25;
    end
    
   

    fi1 = lat(k)*pi/180;
    fi2 = lat_aero*pi/180;
    delta_fi = (lat_aero-lat(k))*pi/180;
    delta_lambda = (lon_aero-lon(k))*pi/180;
    a = sin(delta_fi/2)*sin(delta_fi/2)+cos(fi1)*cos(fi2)*sin(delta_lambda/2)*sin(delta_lambda/2);
    c = 2*atan(sqrt(a)/sqrt(1-a));
    dist(k) = 6371*c;
end
close all;
plot(x, lat);
figure();
plot(x, lon);
figure();
plot(x, roll);
figure();
plot(x, pitch)
figure();
plot(x, yaw)

A = [lon;lat;alt;pitch;roll;yaw];
fileID = fopen('C:\Users\paulo\Dropbox\SAInt\ILS\client_dummy\four_deg_circ_approach.txt','w');
fprintf(fileID,'%f;%f;%f;%f;%f;%f\r\n',A);
fclose(fileID);




