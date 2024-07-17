//-----------Con estas velocidades el robot va super bien. Tarda 13.16, 15.50 Seg en dar una vuelta sin peso y con liga en la rueda trasera.
//////// En general tenemos que velo > veloc > veloci
//#define velo  150 + 30 + 10 + 20        //velocidad a la que girarán las llantas, (1a 35 menos que 2da)
//#define veloc  100 + 10 + 10 + 20
//#define veloci  50 + 10 + 10


//-------------Con estas velocidades el robot va bien. Tarda 13.23, 13.14, 14.49, 13.15 Seg en una vuelta sin peso y con liga en la riueda trasera.
//---Versión final del robot: 11.52, 11.44, 11.60, 11.77, 11.61 seg
//----Aquí hay mayor estabilidada que en máxima velocidad
#define velo  150 + 30 + 10 + 20 + 30        //velocidad a la que girarán las llantas, (1a 35 menos que 2da)
#define veloc  100 + 10 + 10 + 20 + 30
#define veloci  50 + 10 + 10 + 10



//-----------Velocidades para carrito sin peso-----------
//////// En general tenemos que velo > veloc > veloci
//#define velo  150 + 30
//#define veloc  100 + 10
//#define veloci  50 + 10
//------Estas velocidades funcionan bien sin peso (falta probar con sol)-------
//------Al ponerle peso con estas velocidades se logra estabilidad, pero las vueltas en los casos 10000 y 00001 hay que hacerlas más rápidas.


//------Velocidades con velo al máximo-------------------
//-----------Verión final del robot: Con estas velocidad el robot hace 11.66, 11.32 Seg.
//#define velo  150 + 30 + 10 + 20 + 30  + 15     //velocidad a la que girarán las llantas, (1a 35 menos que 2da)
//#define veloc  100 + 10 + 10 + 20 + 30 + 10
//#define veloci  50 + 10 + 10 + 10
