import java.io.*;
import java.util.*;

class Posicion {
  public int Valor;
  public int I;
  public int J;

  public Posicion(int Valor, int I, int J) {
    this.I = I;
    this.J = J;
    this.Valor = Valor;
  }
}

public class Programa_v2 {

  static boolean diagonalLibre(int[][] tablero, int i, int j) {
    int N = tablero.length;
    // Diagonal superior izquierda
    for (int x = i - 1, y = j - 1; x >= 0 && y >= 0; x--, y--)
      if (tablero[x][y] == -1)
        return false;
    // Diagonal superior derecha
    for (int x = i - 1, y = j + 1; x >= 0 && y < N; x--, y++)
      if (tablero[x][y] == -1)
        return false;
    // Diagonal inferior izquierda
    for (int x = i + 1, y = j - 1; x < N && y >= 0; x++, y--)
      if (tablero[x][y] == -1)
        return false;
    // Diagonal inferior derecha
    for (int x = i + 1, y = j + 1; x < N && y < N; x++, y++)
      if (tablero[x][y] == -1)
        return false;

    return true;
  }

  public static void Torres_y_Reinas(int[][] tablero, int Q, int R, int valor) {
    int Final = 0;
    List<Integer> DelRow = new ArrayList<>();
    List<Integer> DelCol = new ArrayList<>();
    List<Posicion> Posiciones = new ArrayList<>();
    for (int j = 0; j < Q + R; j++) {
      for (int i = 0; i < Q + R; i++) {
        Posicion tmp = new Posicion(tablero[i][j], i, j);
        Posiciones.add(tmp);
      }
    }
    Collections.sort(Posiciones, new Comparator<Posicion>() {
      @Override
      public int compare(Posicion a, Posicion b) {
        return b.Valor - a.Valor;
      }
    });

    int index = 0;
    while (Q + R > 0 && index < tablero.length * tablero.length) {
      if (!DelRow.contains(Posiciones.get(index).I) && !DelCol.contains(Posiciones.get(index).J)) {
        if (R > 0) {

          R--;
          DelRow.add(Posiciones.get(index).I);
          DelCol.add(Posiciones.get(index).J);
          tablero[Posiciones.get(index).I][Posiciones.get(index).J] = -1;
          Final += Posiciones.get(index).Valor;
        } else {
          if (diagonalLibre(tablero, Posiciones.get(index).I, Posiciones.get(index).J)) {

            DelRow.add(Posiciones.get(index).I);
            DelCol.add(Posiciones.get(index).J);
            tablero[Posiciones.get(index).I][Posiciones.get(index).J] = -1;
            Q--;
            Final += Posiciones.get(index).Valor;
          }
        }
      }
      index++;
    }
    if (R > 0 || Q > 0) {
      Final = 0;
    }
    System.out.println(Final);
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String line;

    while ((line = br.readLine()) != null) {
      line = line.trim();
      if (line.isEmpty())
        continue;

      StringTokenizer st = new StringTokenizer(line);
      int Q = Integer.parseInt(st.nextToken());
      int R = Integer.parseInt(st.nextToken());

      int N = Q + R;

      int[][] tablero = new int[N][N];

      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {
          tablero[i][j] = Integer.parseInt(st.nextToken());
        }
      }
      Torres_y_Reinas(tablero, Q, R, 0);
    }
  }

}
