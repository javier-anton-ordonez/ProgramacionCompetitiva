import java.io.*;
import java.util.*;

class Posicion {
  public int Valor;
  public int I;
  public int J;
  public boolean Used;

  public Posicion(int Valor, int I, int J) {
    this.I = I;
    this.J = J;
    this.Valor = Valor;
  }
}

class infoTablero {
  boolean[] Columnas;
  boolean[] Filas;

  public infoTablero(int N) {
    this.Filas = new boolean[N];
    this.Columnas = new boolean[N];
  }
}

public class Programa_v4 {

  static int mejorGlobal;
  static int[] diag1, diag2;
  static int[] diagTorre1, diagTorre2;

  static boolean diagonalLibre(int i, int j, int N) {
    int d1 = i - j + N - 1;
    int d2 = i + j;
    return diagTorre1[d1] == 0 && diagTorre2[d2] == 0;
  }

  public static void Torres_y_Reinas(List<Posicion> Posiciones, int start, int[][] tablero, infoTablero info, int Q,
      int R, int N, int valor, int cotaSup) {

    if (Q == 0 && R == 0) {
      mejorGlobal = Math.max(mejorGlobal, valor);
      return;
    }

    if (valor + cotaSup <= mejorGlobal)
      return;

    int restantes = Posiciones.size() - start;
    if (restantes < Q + R)
      return;

    int piezasRestantes = Q + R;
    int sumaMaxPosible = 0;
    int contadas = 0;
    for (int idx = start; idx < Posiciones.size() && contadas < piezasRestantes; idx++) {
      int ti = Posiciones.get(idx).I;
      int tj = Posiciones.get(idx).J;
      if (!info.Filas[ti] && !info.Columnas[tj]) {
        sumaMaxPosible += Posiciones.get(idx).Valor;
        contadas++;
      }
    }
    if (valor + sumaMaxPosible <= mejorGlobal)
      return;

    for (int k = start; k < Posiciones.size(); k++) {
      int i = Posiciones.get(k).I;
      int j = Posiciones.get(k).J;

      if (info.Filas[i] || info.Columnas[j])
        continue;

      int d1 = i - j + N - 1;
      int d2 = i + j;

      if (Q > 0 && diagonalLibre(i, j, N)) {
        info.Columnas[j] = true;
        info.Filas[i] = true;
        diag1[d1]++;
        diag2[d2]++;
        diagTorre1[d1]++;
        diagTorre2[d2]++;

        Torres_y_Reinas(Posiciones, k + 1, tablero, info, Q - 1, R, N, valor + tablero[i][j],
            cotaSup - Posiciones.get(k).Valor);

        info.Columnas[j] = false;
        info.Filas[i] = false;
        diag1[d1]--;
        diag2[d2]--;
        diagTorre1[d1]--;
        diagTorre2[d2]--;
      }

      if (R > 0 && diagonalLibre(i, j, N)) {
        info.Columnas[j] = true;
        info.Filas[i] = true;
        diagTorre1[d1]++;
        diagTorre2[d2]++;

        Torres_y_Reinas(Posiciones, k + 1, tablero, info, Q, R - 1, N, valor + tablero[i][j],
            cotaSup - Posiciones.get(k).Valor);

        info.Columnas[j] = false;
        info.Filas[i] = false;
        diagTorre1[d1]--;
        diagTorre2[d2]--;
      }
    }
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

      List<Posicion> Posiciones = new ArrayList<>();
      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {

          tablero[i][j] = Integer.parseInt(st.nextToken());
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

      mejorGlobal = 0;
      infoTablero info = new infoTablero(N);

      diag1 = new int[2 * N - 1];
      diag2 = new int[2 * N - 1];
      diagTorre1 = new int[2 * N - 1];
      diagTorre2 = new int[2 * N - 1];

      int cotaSup = 0;
      for (int i = 0; i < N && i < Posiciones.size(); i++) {
        cotaSup += Posiciones.get(i).Valor;
      }

      Torres_y_Reinas(Posiciones, 0, tablero, info, Q, R, tablero.length, 0, cotaSup);
      System.out.println(mejorGlobal);

    }
  }

}
