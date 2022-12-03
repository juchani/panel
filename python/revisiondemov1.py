from pyModbusTCP.client import ModbusClient
from influxdb import InfluxDBClient as influx
import math 
import datetime
from time import sleep as t

cliente = influx(database='marcodb')
lim_m=6
lim_t=19
global va
va=True
lat=-31.41733910
lon=-64.183319
gtm=-3
luz=0
ip1="192.168.0.66"
def monitoreo():
    ####################PANEL 4 (FIJO)
    a=ModbusClient(host="192.168.25.66", port=502, unit_id=1, auto_open=True)################PANEL FIJO#####################  
    regs = a.read_holding_registers(109, 4)
    if(regs is not None):
        if(regs[1]is not 0 or regs[2]is not 0):
            data = []
            data.append("CORRIENTE,tag=g{} val={}".format(4,regs[0]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=g{} val={}".format(4,regs[1]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((regs[1]/10)*(regs[0]/1000))
            data = []
            data.append("POTENCIA,tag=g{} val={}".format(4,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
            data = []
            data.append("CORRIENTE,tag=s{} val={}".format(4,regs[2]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=s{} val={}".format(4,regs[3]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs[3])/10)*(int(regs[2])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=s{} val={}".format(4,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
            
    ####################PANEL 2 (EJE Y)
    b=ModbusClient(host="192.168.23.73", port=502, unit_id=1, auto_open=True)################PANEL FIJO#####################  
    regs1 = b.read_holding_registers(109, 4)
    if(regs1 is not None):
        if(regs1[1]is not 0 and regs1[0]is not 0):
            data = []
            data.append("CORRIENTE,tag=s{} val={}".format(2,regs1[0]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=s{} val={}".format(2,regs1[1]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs1[1])/10)*(int(regs1[0])/1000))
            data = []
            data.append("POTENCIA,tag=s{} val={}".format(2,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
            data = []
            data.append("CORRIENTE,tag=g{} val={}".format(2,regs1[2]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=g{} val={}".format(2,regs1[3]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs1[3])/10)*(int(regs1[2])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=g{} val={}".format(2,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
     ####################PANEL 3 (EJE X)
    c=ModbusClient(host="192.168.23.23", port=502, unit_id=1, auto_open=True)################PANEL FIJO#####################  
    regs2 = c.read_holding_registers(109, 4)
    if(regs2 is not None):
        if(regs2[1]is not 0 and regs2[0]is not 0):
            data = []
            data.append("CORRIENTE,tag=s{} val={}".format(3,regs2[0]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=s{} val={}".format(3,regs2[1]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs2[1])/10)*(int(regs2[0])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=s{} val={}".format(3,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
            data = []
            data.append("CORRIENTE,tag=g{} val={}".format(3,regs2[2]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=g{} val={}".format(3,regs2[3]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs2[3])/10)*(int(regs2[2])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=g{} val={}".format(3,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
     ####################PANEL 1 (EJE X-Y)
    d=ModbusClient(host="192.168.23.3", port=502, unit_id=1, auto_open=True)################PANEL FIJO#####################  
    regs3 = d.read_holding_registers(109, 4)
    if(regs3 is not None):
        if(regs3[1]is not 0 or regs3[0]is not 0):
            print(regs3)
            data = []
            data.append("CORRIENTE,tag=s{} val={}".format(1,regs3[0]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=s{} val={}".format(1,regs3[1]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs3[1])/10)*(int(regs3[0])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=s{} val={}".format(1,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            
            data = []
            data.append("CORRIENTE,tag=g{} val={}".format(1,regs3[2]/1000))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            data = []
            data.append("VOLTAJE,tag=g{} val={}".format(1,regs3[3]/10))
            cliente.write_points(data, database='', time_precision='s', protocol='line')
            potencia=((int(regs3[3])/10)*(int(regs3[2])/1000))
            print(potencia)
            data = []
            data.append("POTENCIA,tag=g{} val={}".format(1,potencia))
            cliente.write_points(data, database='', time_precision='s', protocol='line')

    
 
 
            
    
#       c = ModbusClient(host="192.168.53.80", port=502, unit_id=1, auto_open=True)
#    regs = c.read_holding_registers(108, 3)
#    luz=regs[0]     
#    data = []
#    data.append("LUZ,tag=s{} val={}".format(1,regs[0]))
#    cliente.write_points(data, database='', time_precision='s', protocol='line')
#    data = []
#    data.append("CORRIENTE,tag=s{} val={}".format(1,regs[1]))
#    cliente.write_points(data, database='', time_precision='s', protocol='line')
#    data = []
#    data.append("VOLTAJE,tag=s{} val={}".format(1,regs[2]/10))
#    cliente.write_points(data, database='', time_precision='s', protocol='line')
    
def posicion_sol(i,mi):    
    if(i>lim_m and i<lim_t):
        hora=i+math.radians(mi)
        b=0.98630*(dia-81)
        lstm=15*gtm
        et=9.87*math.sin(math.radians(b*2))-(7.53*math.cos(math.radians(b)))-(1.5*math.sin(math.radians(b)))
        tc=4*(lon-lstm)+(et);
        lst=hora+(tc/60);
        w=(lst-12)* 15;
        s=23.45*math.sin(math.radians((360/365)*(284+dia))) 
        h=math.asin(math.sin(math.radians(s))*math.sin(math.radians(lat))+math.cos(math.radians(s))*math.cos(math.radians(lat))*math.cos(math.radians(w)))
        h=math.degrees(h)
        if(w<0):
            l=math.acos((math.sin(math.radians(s))*math.cos(math.radians(lat))-math.cos(math.radians(s))*math.sin(math.radians(lat))*math.cos(math.radians(w)))/math.cos(math.radians(h)))
            l=math.degrees(l)
        if(w>0):
            l=math.acos((math.sin(math.radians(s))*math.cos(math.radians(lat))-math.cos(math.radians(s))*math.sin(math.radians(lat))*math.cos(math.radians(w)))/math.cos(math.radians(h)))
            l=360-math.degrees(l)
        f=math.radians(30)
        ##quitar comillas para ver valores 
        """print("B ");
        print(b);
        print(" LSTM ");
        print(lstm);
        print(" ET ");
        print(et);
        print(" TC ");
        print(tc);
        print(" LST ");
        print(lst);
        print(" w ");
        print(w);
        print(" S ");
        print(s);"""
        print("Hora={}:{} H={}  L={}".format(i,mi,h,l))
         ####################PANEL 1 (EJE X-Y)
        a = ModbusClient(host="192.168.0.3", port=502, unit_id=1, auto_open=True)
        #
        a.write_single_register(101, int(l))
        t(5)
        a.write_single_register(107, int(h))
        ####################PANEL 2 (EJE Y)
        b = ModbusClient(host="192.168.0.73", port=502, unit_id=1, auto_open=True)
        b.write_single_register(107, int(h))          
        ####################PANEL 3 (EJE X)
        c = ModbusClient(host="192.168.0.23", port=502, unit_id=1, auto_open=True)
        c.write_single_register(101, int(l))          
                 

 
 #       b = ModbusClient(host="192.168.0.30", port=502, unit_id=1, auto_open=True)
 #       if(h>15):
 #           b.write_single_register(107, int(h))          
 #       if(h>15):
 #           b.write_single_register(101, int(l))
        
            

    print("Hora={}:{}".format(i,mi))
def pos_ini(h,m):
    global va
    if(h>lim_m and h<lim_t):
        va=True
        return True
    else:
        if(va==True):  
            t(5)
            a = ModbusClient(host="192.168.0.3", port=502, unit_id=1, auto_open=True)
            a.write_single_register(113, 100)
            t(5)
            b = ModbusClient(host="192.168.0.73", port=502, unit_id=1, auto_open=True)
            b.write_single_register(107, 30)
            t(5)
            c = ModbusClient(host="192.168.0.23", port=502, unit_id=1, auto_open=True)
            c.write_single_register(113, 100)          
            t(5)
            de = ModbusClient(host="192.168.0.3", port=502, unit_id=1, auto_open=True)
            de.write_single_register(107, 30)
            t(5)
        return False
        
    
while 1:
    try:
        dt = datetime.datetime.now()
        dia =int(dt.strftime("%j"))
        hora=int(dt.strftime("%H"))
        minuto=int(dt.strftime("%M"))
        monitoreo()
        if(pos_ini(hora,minuto)):
            posicion_sol(hora,minuto)
        t(0.5)
    except:
        print("error de conexión")
 

