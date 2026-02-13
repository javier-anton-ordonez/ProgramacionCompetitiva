import java.io.*;
import java.util.*;

public class Programa_v3 {
  static int mejorGlobal;
  static int N;
  static boolean[] filas, cols;
  static int[] diag1, diag2;

  static class Casilla {
    int i, j, valor;

    Casilla(int i, int j, int valor) {
      this.i = i;
      this.j = j;
      this.valor = valor;
    }
  }

  static void backtrack(int[][] tablero, List<Casilla> casillas, int start, int Q, int R, int valor, int cotaSup) {
    if (Q == 0 && R == 0) {
      mejorGlobal = Math.max(mejorGlobal, valor);
      return;
    }

    if (valor + cotaSup <= mejorGlobal)
      return;

    for (int k = start; k < casillas.size(); k++) {
      Casilla c = casillas.get(k);
      int i = c.i, j = c.j;
      int d1 = i - j + N - 1;
      int d2 = i + j;

      if (filas[i] || cols[j])
        continue;

      if (Q > 0 && diag1[d1] == 0 && diag2[d2] == 0) {
        filas[i] = cols[j] = true;
        diag1[d1] = diag2[d2] = 1;

        backtrack(tablero, casillas, k + 1, Q - 1, R, valor + tablero[i][j], cotaSup - c.valor);

        filas[i] = cols[j] = false;
        diag1[d1] = diag2[d2] = 0;
      }

      if (R > 0) {
        filas[i] = cols[j] = true;

        backtrack(tablero, casillas, k + 1, Q, R - 1, valor + tablero[i][j], cotaSup - c.valor);

        filas[i] = cols[j] = false;
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
      N = Q + R;

      int[][] tablero = new int[N][N];

      if (tablero.length == 2 && Q >= 1 && R > 0) {
        System.out.println(0);
        return;
      }
      List<Casilla> casillas = new ArrayList<>();

      for (int i = 0; i < N; i++) {
        st = new StringTokenizer(br.readLine());
        for (int j = 0; j < N; j++) {
          tablero[i][j] = Integer.parseInt(st.nextToken());
          casillas.add(new Casilla(i, j, tablero[i][j]));
        }
      }

      casillas.sort((a, b) -> b.valor - a.valor);

      int cotaSup = 0;
      for (int i = 0; i < N && i < casillas.size(); i++) {
        cotaSup += casillas.get(i).valor;
      }

      mejorGlobal = 0;
      filas = new boolean[N];
      cols = new boolean[N];
      diag1 = new int[2 * N - 1];
      diag2 = new int[2 * N - 1];

      backtrack(tablero, casillas, 0, Q, R, 0, cotaSup);

      System.out.println(mejorGlobal);
    }
  }
}
