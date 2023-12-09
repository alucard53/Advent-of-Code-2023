package org.example;

import java.io.FileInputStream;
import java.util.*;
import java.util.stream.Collectors;

public class d9p2 {

    public static void main(String args[]) throws Exception {
        FileInputStream fis = new FileInputStream("input.txt");
        Scanner in = new Scanner(fis);
        int m = 200;
        int sum = 0;

        while (m-- > 0) {
            List<List<Integer>> data = new ArrayList<>();

            data.add(Arrays.stream(in.nextLine().split(" ")).map((s -> Integer.parseInt(s))).collect(Collectors.toList()));
            int n = data.get(0).size();

            int i = 1;
            while (true) {
                data.add(new ArrayList<>());
                int zeroes = 0;
                for (int j = 0; j < n - i; j++) {
                    int next = data.get(i - 1).get(j + 1) - data.get(i - 1).get(j);
                    if (next == 0) {
                        zeroes++;
                    }
                    data.get(i).add(next);
                }
                if (zeroes == n - i) {
                    break;
                }
                i++;
            }
            data.forEach(d -> d.add(0, 0));
            for (int j = data.size() - 2; j >= 0; j--) {
                int nCurr = data.get(j).size();
                int nPrev = data.get(j + 1).size();

                data.get(j).set(0, data.get(j).get(1) - data.get(j + 1).get(0));
            }
            // System.out.println(data);
            sum += data.get(0).get(0);

            data = null;
            System.gc();
        }
        System.out.println(sum);
    }
}
