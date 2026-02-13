import java.io.*;
import java.util.*;

class infoTablero {
  boolean[] Columnas;
  boolean[] Filas;

  public infoTablero(int N) {
    this.Filas = new boolean[N];
    this.Columnas = new boolean[N];
  }
}

public class Programa_v2 {
  static int mejorGlobal;

  static boolean diagonalLibre(boolean[][] esReina, int i, int j, int N) {
    /*
     * // Diagonal superior izquierda
     * for (int x = i - 1; x >= 0; x--) {
     * for (int y = j - 1; y >= 0; y--) {
     * if (esReina[x][y])
     * return false;
     * }
     * for (int y = j + 1; y < N; y++) {
     * if (esReina[x][y])
     * return false;
     * }
     * 
     * }
     * 
     * // Diagonal inferior derecha
     * for (int x = i + 1; x < N; x++) {
     * for (int y = j - 1; y >= 0; y--) {
     * if (esReina[x][y])
     * return false;
     * }
     * 
     * for (int y = j + 1; y < N; y++) {
     * if (esReina[x][y])
     * return false;
     * }
     * }
     */
    int radio = 1;

    int salido[] = { 0, 0, 0, 0 };

    N = N - 1;
    do {

      if (i - radio < 0) {
        salido[0] = 1;
      }

      if (i + radio > N) {
        salido[1] = 1;
      }

      if (j + radio > N) {
        salido[2] = 1;
      }

      if (j - radio < 0) {
        salido[3] = 1;
      }

      if (esReina[Math.max(i - radio, 0)][Math.max(j - radio, 0)]) {
        return false;
      }
      if (esReina[Math.max(i - radio, 0)][Math.min(j + radio, N)]) {
        return false;
      }
      // System.out.println(Math.min(i + radio, N));
      // System.out.println(Math.max(j - radio, 0));
      if (esReina[Math.min(i + radio, N)][Math.max(j - radio, 0)]) {
        return false;
      }
      if (esReina[Math.min(i + radio, N)][Math.min(j + radio, N)]) {
        return false;
      }
      radio++;
    } while (salido[0] + salido[1] + salido[2] + salido[3] < 4);
    return true;
  }

  public static void Torres_y_Reinas(int[][] tablero, boolean[][] esReina, int Q, int R, int valor, infoTablero info) {
    if (Q == 0 && R == 0) {
      mejorGlobal = Math.max(mejorGlobal, valor);
      return;
    }

    int N = tablero.length;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {

        if (Q > 0 && !info.Filas[i] && !info.Columnas[j] && diagonalLibre(esReina, i, j, N)) {
          info.Columnas[j] = true;
          info.Filas[i] = true;
          esReina[i][j] = true;
          Torres_y_Reinas(tablero, esReina, Q - 1, R, valor + tablero[i][j], info);

          info.Columnas[j] = false;
          info.Filas[i] = false;
          esReina[i][j] = false;
        }

        if (R > 0 && !info.Filas[i] && !info.Columnas[j] && diagonalLibre(esReina, i, j, N)) {
          info.Columnas[j] = true;
          info.Filas[i] = true;

          Torres_y_Reinas(tablero, esReina, Q, R - 1, valor + tablero[i][j], info);

          info.Columnas[j] = false;
          info.Filas[i] = false;
        }
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
      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {
          tablero[i][j] = Integer.parseInt(st.nextToken());
        }
      }
      if (tablero.length == 2 && Q >= 1 && R > 0) {
        System.out.println(0);
        return;
      }

      mejorGlobal = 0;
      infoTablero info = new infoTablero(N);
      boolean[][] esReina = new boolean[N][N];

      Torres_y_Reinas(tablero, esReina, Q, R, 0, info);

      System.out.println(mejorGlobal);
    }
  }
}
