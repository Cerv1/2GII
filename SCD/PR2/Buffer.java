import monitor.*;

// -----------------------------------------------------------------------------------------------//

class Buffer extends AbstractMonitor{
  private int numSlots=0;
  private int contador=0;
  private double[] buffer=null;
  private Condition puede_depositar;
  private Condition puede_extraer;

  public Buffer(int numSlots){
    this.numSlots=numSlots;
    buffer=new double[numSlots];
    puede_depositar=makeCondition();
    puede_extraer=makeCondition();
  }

  public void depositar(double valor){
    enter();

    while(contador == numSlots){
      puede_depositar.await();
    }

    buffer[contador]=valor;
    contador++;
    puede_extraer.signal();

    leave();

  }

  public double extraer(){
    enter();

    double valor;
    while(contador==0){
      puede_extraer.await();
    }

    contador--;
    valor=buffer[contador];
    puede_depositar.signal();

    leave();
    return valor;
  }

}

// -----------------------------------------------------------------------------------------------/

class Consumidor implements Runnable{
  private Buffer buffer;
  private int veces;
  private int numC;
  private Thread thr;

  public Consumidor(Buffer buffer, int veces, int numC){
    this.buffer=buffer;
    this.veces=veces;
    this.numC=numC;
  }

  public void run(){
    while(true){
      for(int i=0; i<veces; i++){
        double item=buffer.extraer();
        System.out.println("Consumiendo "+item);
        aux.dormir_max(1000);
      }
    }

  }

}


// _._ _..._ .-',     _.._(`))
// '-. `     '  /-._.-'    ',/
//    )         \            '.
//   / _    _    |             \                In a few days I'll be bacon.
//  |  a    a    /              |
//  \   .-.                     ;
//  '-('' ).-'       ,'       ;
//     '-;           |      .'
//         \           \    /
//         | 7  .__  _.-\   \
//         | |  |  ``/  /`  /
//        /,_|  |   /,_/   /
//           /,_/      '`-'
// -----------------------------------------------------------------------------------------------/

class Productor implements Runnable{
  private Buffer buffer;
  int veces;

  int numP;
  Thread thr;

  public Productor(Buffer buffer, int veces, int numP){
    this.buffer=buffer;
    this.veces=veces;
    this.numP=numP;
  }

  public void run(){
    while(true){
      double item=100*numP;
      for(int i=0; i<veces; i++){
        buffer.depositar(item);
        System.out.println("Produciendo "+item);
        aux.dormir_max(1000);
      }
    }
  }
}

// -----------------------------------------------------------------------------------------------/

class PC{
  public static void main(String[] args){
    Buffer buffer=new Buffer(10);
    Thread[] HebrasProd = new Thread[2];
    Thread[] HebrasCons = new Thread[4];

    for(int i=0; i<2; i++){
      HebrasProd[i] = new Thread(new Productor(buffer, 1, 4));
    }

    for(int i=0; i<4; i++){
      HebrasCons[i] = new Thread(new Consumidor(buffer, 2, 3));
    }

    for(int i=0; i<2; i++){
      HebrasProd[i].start();
    }
    for(int i=0; i<4; i++){
      HebrasCons[i].start();
    }

  }
}
