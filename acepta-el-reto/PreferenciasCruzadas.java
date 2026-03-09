import java.util.*;

class Palabra {
  public Set<Integer> linea;
  public String palabra;

  public Palabra(String palabra) {
    this.palabra = palabra;
    this.linea = new HashSet<>();
  }

  public void addLinea(int numero) {
    this.linea.add(numero);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof Palabra))
      return false;
    Palabra otra = (Palabra) obj;
    return this.palabra.equals(otra.palabra);
  }

  @Override
  public int hashCode() {
    return palabra.hashCode();
  }
}

public class PreferenciasCruzadas {

  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);

    while (true) {
      int N = sc.nextInt();
      if (N == 0) break;
      sc.nextLine();

      Map<String, Palabra> mapaPalabras = new HashMap<>();
      for (int i = 0; i < N; i++) {
        String linea = sc.nextLine();
        String[] palabras = linea.split(" ");
        for (int j = 0; j < palabras.length; j++) {

          String palabraLimpia = palabras[j].replaceAll("[^a-zA-Z]", "").toLowerCase();
          if (palabraLimpia.length() > 2) {
            Palabra p = mapaPalabras.get(palabraLimpia);
            if (p != null) {
              p.addLinea(i + 1);
            } else {
              Palabra tmp = new Palabra(palabraLimpia);
              tmp.addLinea(i + 1);
              mapaPalabras.put(palabraLimpia, tmp);
            }
          }
        }

      }

      List<Palabra> ListaPalabras = new ArrayList<>(mapaPalabras.values());
      Collections.sort(ListaPalabras, new Comparator<Palabra>() {
        @Override
        public int compare(Palabra a, Palabra b) {
          return a.palabra.compareTo(b.palabra);
        }
      });

      for (int j = 0; j < ListaPalabras.size(); j++) {
        System.out.print(ListaPalabras.get(j).palabra);
        List<Integer> lineasOrdenadas = new ArrayList<>(ListaPalabras.get(j).linea);
        Collections.sort(lineasOrdenadas);
        for (int i = 0; i < lineasOrdenadas.size(); i++) {
          System.out.print(" " + lineasOrdenadas.get(i));
        }
        System.out.println();
      }
      System.out.println("----");
    }
    sc.close();
  }
}
