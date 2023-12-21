const std = @import("std");
const print = std.debug.print;

const Empty = struct {};

pub fn bfs(grid: [131][131]u8) !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    var q = std.ArrayList([3]i32).init(allocator);

    try q.insert(0, [_]i32{ 65, 65, 0 });

    var vis = [_][131]bool{[_]bool{false} ** 131} ** 131;

    const dirs = [_][2]i32{
        [_]i32{ 0, -1 },
        [_]i32{ 0, 1 },
        [_]i32{ 1, 0 },
        [_]i32{ -1, 0 },
    };

    var seen = std.AutoHashMap([2]i32, Empty).init(allocator);

    while (q.items.len > 0) {
        const curr = q.orderedRemove(0);
        const i = curr[0];
        const j = curr[1];
        const steps: usize = @intCast(curr[2]);

        if (vis[@intCast(i)][@intCast(j)]) {
            continue;
        }

        vis[@intCast(i)][@intCast(j)] = true;

        if (steps <= 64 and steps % 2 == 0) {
            try seen.put([_]i32{ i, j }, Empty{});
        }

        for (dirs) |dir| {
            const m = i + dir[0];
            const n = j + dir[1];

            if (0 <= m and m < grid.len and 0 <= n and n < grid[0].len and grid[@intCast(m)][@intCast(n)] != '#') {
                try q.insert(q.items.len, [_]i32{ m, n, @intCast(steps + 1) });
            }
        }
    }
    print("{}", .{seen.count()});
}

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input.txt", .{});
    const buffered_reader = @constCast(&std.io.bufferedReader(file.reader()));

    var input: [17423]u8 = undefined;

    _ = try buffered_reader.read(@constCast(&input));
    file.close();

    var grid: [131][131]u8 = undefined;

    var k: usize = 0;

    var i: u32 = 0;
    while (i < 131) : (i += 1) {
        var j: u32 = 0;
        while (j < 131) : (j += 1) {
            grid[i][j] = input[k];
            k += 1;
        }
        k += 2;
    }

    try bfs(grid);
}
