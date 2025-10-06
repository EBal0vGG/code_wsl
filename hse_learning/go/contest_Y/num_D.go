package main

import (
    "bufio"
    "fmt"
    "os"
)

func min3(a, b, c uint16) uint16 {
    if a > b {
        a = b
    }
    if a > c {
        a = c
    }
    return a
}

func max(a, b uint16) uint16 {
    if a > b {
        return a
    }
    return b
}

func main() {
    reader := bufio.NewReaderSize(os.Stdin, 1<<20)
    writer := bufio.NewWriterSize(os.Stdout, 1<<20)
    defer writer.Flush()

    var n, m, d int
    fmt.Fscan(reader, &n, &m, &d)

    size := n * m
    dist := make([]uint16, size)
    for i := range dist {
        dist[i] = 0xFFFF
    }

    qx := make([]int, 0, size)
    qy := make([]int, 0, size)

    for i := 0; i < n; i++ {
        var line string
        fmt.Fscan(reader, &line)
        for j := 0; j < m; j++ {
            if line[j] == 'x' || line[j] == 'X' {
                idx := i*m + j
                dist[idx] = 0
                qx = append(qx, i)
                qy = append(qy, j)
            }
        }
    }

    dir := [5]int{-1, 0, 1, 0, -1}
    head := 0
    for head < len(qx) {
        x, y := qx[head], qy[head]
        currDist := dist[x*m+y]
        head++
        for k := 0; k < 4; k++ {
            nx := x + dir[k]
            ny := y + dir[k+1]
            if nx >= 0 && nx < n && ny >= 0 && ny < m {
                idx := nx*m + ny
                if dist[idx] == 0xFFFF {
                    dist[idx] = currDist + 1
                    qx = append(qx, nx)
                    qy = append(qy, ny)
                }
            }
        }
    }

    curr := make([]uint16, m)
    prev := make([]uint16, m)

    var ans uint16 = 0
    for i := 0; i < n; i++ {
        for j := 0; j < m; j++ {
            idx := i*m + j
            if int(dist[idx]) < d {
                curr[j] = 0
            } else {
                if i == 0 || j == 0 {
                    curr[j] = 1
                } else {
                    curr[j] = min3(prev[j], curr[j-1], prev[j-1]) + 1
                }
                ans = max(ans, curr[j])
            }
        }
        curr, prev = prev, curr
    }

    fmt.Fprintln(writer, ans)
}
