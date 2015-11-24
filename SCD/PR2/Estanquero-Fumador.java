import monitor.*;

// -----------------------------------------------------------------------------------------------//

class Estanco extends AbstractMonitor{
    private int condicion=-1;
    private Condition[] fumador = new Condition[3];
    private Condition estanquero;

    public Estanco() {
      for (int i=0; i<fumador.length; i++)
        fumador[i]=makeCondition();

      estanquero = makeCondition();
    }

  //Invocado por cada fumador, indicando su ingrediente o número.
  public void obtenerIngrediente(int miIngrediente){
    enter();

    if(condicion != miIngrediente){
      this.fumador[miIngrediente].await();
    }

    if (miIngrediente == 0){
     System.out.println("El primer fumador coge las cerillas y se va a fumar.");
    }
    else if(miIngrediente == 1){
      System.out.println("El segundo fumador coge el tabaco y se va a fumar.");
    }
    else
      System.out.println("El tercer fumador coge el papel y se va a fumar.");

    condicion=-1;
    estanquero.signal();


    leave();
  }

  //Invocado por el estanquero, indicando el ingrediente que pone.
  public void ponerIngrediente(int ingrediente){
    enter();

    if(ingrediente == 0){
			System.out.println("El estanquero saca cerillas. ");

    }
		else if(ingrediente == 1){
			System.out.println("El estanquero saca tabaco. ");

    }
		else{
			System.out.println("El estanquero saca papel. ");

    }
    condicion=ingrediente;
    fumador[condicion].signal();
    leave();
  }

  //Invocado por el estanquero.
  public void esperarRecogidaIngrediente(){
    enter();
    if(condicion!=-1)
      estanquero.await();

    leave();
  }

}

// -----------------------------------------------------------------------------------------------//

class Estanquero implements Runnable{
  public Thread thr;
  private Estanco estanco;

  public Estanquero(Estanco estanco){
    this.estanco=estanco;
  }

  public void run(){
    int ingrediente;
    while(true){
      ingrediente=(int)(Math.random () * 3.0); // 0, 1 ó 2.
      estanco.ponerIngrediente(ingrediente);
      estanco.esperarRecogidaIngrediente();
    }
  }

}

// -----------------------------------------------------------------------------------------------//

class Fumador implements Runnable{
  private int miIngrediente;
  private Estanco estanco;

  public Fumador(int p_miIngrediente, Estanco estanco){
    this.miIngrediente = p_miIngrediente;
    this.estanco = estanco;
  }

  public void run(){
    while(true){
      estanco.obtenerIngrediente(miIngrediente);
      aux.dormir_max(2000);
    }
  }

}

class EF{

  public static void main(String[] args){
    Estanco estanco = new Estanco();
    Thread hebraEstanquero = new Thread(new Estanquero(estanco));
    Thread[] hebraFumador = new Thread[3];

    hebraFumador[0] = new Thread(new Fumador(0, estanco), "El primer fumador");
    hebraFumador[1] = new Thread(new Fumador(1, estanco), "El segundo fumador");
    hebraFumador[2] = new Thread(new Fumador(2, estanco), "El tercer fumador");
    hebraEstanquero.start();

    for(int i=0; i<hebraFumador.length; i++){
       hebraFumador[i].start();
    }

  }

}
