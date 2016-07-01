% Matlab + Arduino Serial Port communication
% Autor: Mario P�rez Esteso - Geeky Theory
% Blog: www.geekytheory.com
% Facebook Page: www.facebook.com/geekytheory
% Twitter: @geekytheory

close all;
clc;


% AVI --------
%Configuraci�n del gr�fico
plano = figure();
f1 = 2;
f2 = 3;
vocal = 'a';


h = plot(f2,f1,'rx','LineWidth',2);
grid on;
xlim([500 3500]);
ylim([200 1200]);
set(gca,'XDir','reverse')
set(gca,'YDir','reverse')
hold on;
set(h,'XDataSource','f2');
set(h,'YDataSource','f1');


%Vocales
a_f2 = 1300;
a_f1 = 789;
e_f2 = 2100;
e_f1 = 443;
i_f2 = 2500;
i_f1 = 300;
o_f2 = 815;
o_f1 = 467;
u_f2 = 741;
u_f1 = 331;

circulo(a_f2,a_f1,100);
circulo(e_f2,e_f1,100);
circulo(i_f2,i_f1,100);
circulo(o_f2,o_f1,100);
circulo(u_f2,u_f1,100);


%------------
y=zeros(1,1000); %Vector donde se guardar�n los datos

%Inicializo el puerto serial que utilizar�
delete(instrfind({'Port'},{'COM3'}));
puerto_serial=serial('COM3');
puerto_serial.BaudRate=115200;
warning('off','MATLAB:serial:fscanf:unsuccessfulRead');

%Abro el puerto serial
fopen(puerto_serial); 

%Declaro un contador del n�mero de muestras ya tomadas
contador_muestras=1;

% %Creo una ventana para la gr�fica
% figure('Name','Serial communication: Matlab + Arduino. Mario P�rez Esteso')
% title('SERIAL COMMUNICATION MATLAB+ARDUINO');
% xlabel('N�mero de muestra');
% ylabel('Voltaje (V)');
% grid on;
% hold on;

%Bucle while para que tome y dibuje las muestras que queremos
while contador_muestras<=5000
%         ylim([0 5.1]); 
%         xlim([contador_muestras-20 contador_muestras+5]);
%         valor_potenciometro=fscanf(puerto_serial,'%d')';
%         y(contador_muestras)=(valor_potenciometro(1))*5/1024;
%         plot(contador_muestras,y(contador_muestras),'X-r');        
%         drawnow
         contador_muestras=contador_muestras+1;
    d = fscanf(puerto_serial,'%f');
    f1 = d(1);
    f2 = d(2);
    vocal = d(3);
%     plot(f2,f1,'r*');
    refreshdata;
    drawnow
end

%Cierro la conexi�n con el puerto serial y elimino las variables
fclose(puerto_serial); 
delete(puerto_serial);
clear all;