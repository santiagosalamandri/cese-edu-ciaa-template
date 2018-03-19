/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"        // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/
#define FULLTIME 100
#define HALFTIME FULLTIME/2

/*==================[definiciones de datos internos]=========================*/

DEBUG_PRINT_ENABLE
CONSOLE_PRINT_ENABLE

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_USB como salida Serial de debug
   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintlnString( "DEBUG: UART_USB configurada." );
   
   // Inicializar UART_232 como salida Serial de consola
//   consolePrintConfigUart( UART_232, 115200 );
//   consolePrintlnString( "UART_232 configurada." );

   // Crear varias variables del tipo booleano
   bool_t tec2Value = ON;
   bool_t tec1Value = ON;

   /*Variables que almacenan el estado anterior de cada tecla*/
   bool_t lastTec1Value = ON;
   bool_t lastTec2Value=ON;

   bool_t ledbValue = OFF;


   int delayMs=FULLTIME;
   int colores[3]={LEDR,  LEDG,  LEDB};
   int selectorDeColor=0;

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {

      tec1Value = gpioRead( TEC1 ); //Leo si se presiono tecla 1

      if(tec1Value == OFF){
    	  if( lastTec1Value==ON)	//Verifico que se presiono la tecla 1 y que ademas no estaba presionada desde la anterior iteracion
    	  {
    		  lastTec1Value=OFF;
    		  delayMs=(delayMs==FULLTIME)?HALFTIME:FULLTIME;	//vario la frecuencia segun el valor anterior
    		  consolePrintlnString( "Cambio la frecuencia." );
			  consolePrintEnter();
    	  }
      }
      else{
    	  lastTec1Value=ON;
      }

      tec2Value = gpioRead( TEC2 );

      if(tec2Value == OFF){		//Verifico que se presiono la tecla 2 y que ademas no estaba presionada desde la anterior iteracion
          	  if(lastTec2Value==ON)
          	  {
			  lastTec2Value=OFF;
			  selectorDeColor++;
			  selectorDeColor=selectorDeColor%3;		//Vario la posicion del array que contiene los colores
			  consolePrintlnString( "Cambio color " );
			  consolePrintEnter();
          	  }

            }
		else{
			lastTec2Value=ON;
		}


      int j=0;

      for(j=LEDR;j<LED1;j++){	//hago toggle del led que correponde y apago los demas
			if(j!=colores[selectorDeColor]){
				gpioWrite(j,OFF);
			}
			else{
				  gpioToggle( colores[selectorDeColor] );
			}
      }

      /* Retardo bloqueante */
      delay( delayMs );

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
