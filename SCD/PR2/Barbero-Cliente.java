import monitor.*;

// -----------------------------------------------------------------------------------------------//

class Barberia extends AbstractMonitor{

  private boolean barberia_ocupada;
  public final int numeroClientes=5;

  private Condition barbero;
  private Condition salaDeEspera;

  // Inicializa las colas de las condiciones.
  public Barberia(){
    barberia_ocupada=false;
    salaDeEspera=makeCondition();
    barbero=makeCondition();
  }

  // Invocado por los clientes para cortarse el pelo.
  public void cortarPelo(){
    enter();
    if(barberia_ocupada){
      System.out.print("El barbero esta ocupado y ");
      System.out.println(Thread.currentThread().getName() +" se va a la sala de espera.");
      barbero.await();
    }

      System.out.println("El barbero esta libre. Puede pelarse.");
      barberia_ocupada=true;
      salaDeEspera.signal();
      System.out.print("Se pone a pelar a ");
      System.out.println(Thread.currentThread().getName());



    leave();
  }

  // Invocado por el barbero para esperar (si procede) a un nuevo cliente y sentarlo para el corte.
  public void siguienteCliente(){
    enter();
    salaDeEspera.signal();
    leave();

    // Give up and hire f*cking dragons.

  }

  // Invocado por el barbero para indicar que ha terminado de cortar el pelo.
  public void finCliente(){
    enter();
    System.out.println("Fin del cliente actual. ");
    barberia_ocupada=false;
    barbero.signal();
    leave();
  }

}

// -----------------------------------------------------------------------------------------------//

class Cliente implements Runnable{
  public Thread thr;
  private Barberia barberia;

  //Constructor de las hebras cliente.
  public Cliente(Barberia barberia){
    this.barberia=barberia;
  }

  // Método que ejecutan las hebras cliente.
  public void run(){
    while(true){
      barberia.cortarPelo();     // El cliente espera (si procede) y se corta el pelo.
      aux.dormir_max( 3000 );     // El cliente está fuera de la barberia un tiempo.
    }
  }

}

// -----------------------------------------------------------------------------------------------//

class Barbero implements Runnable{
  public Thread thr;
  private Barberia barberia;
  private String nombre;

  // Constructor de la hebra barbero.
  public Barbero(Barberia barberia, String nombre){
    this.barberia=barberia;
    this.nombre=nombre;
  }

  // Método que ejecuta la hebra barbero.
  public void run(){
    while(true){
      barberia.siguienteCliente();
      aux.dormir_max( 1000 );           // El barbero está cortando el pelo
      barberia.finCliente ();
    }
  }

}

// -----------------------------------------------------------------------------------------------//

class BC{
  public static void main(String[] args){
    Barberia barberia = new Barberia();
    Thread HebraBarbero = new Thread(new Barbero(barberia, "Barbero"));
    Thread[] HebraClientes  = new Thread[barberia.numeroClientes];
    HebraClientes[0] = new Thread(new Cliente(barberia), "Cliente 1.");
    HebraClientes[1] = new Thread(new Cliente(barberia), "Cliente 2.");
    HebraClientes[2] = new Thread(new Cliente(barberia), "Cliente 3.");
    HebraClientes[3] = new Thread(new Cliente(barberia), "Cliente 4.");
    HebraClientes[4] = new Thread(new Cliente(barberia), "Cliente 5.");

    for(int i=0; i<barberia.numeroClientes; i++){
      HebraClientes[i].start();
    }


    HebraBarbero.start();




  }
}
