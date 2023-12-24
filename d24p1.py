import math

input = open('input.txt').read().strip().split('\n')

slopes = []
intercepts = []
pos = []
vel = []


for line in input:
    p = list(map(int ,line.split('@')[0].strip().split(', ')))
    v = list(map(int ,line.split('@')[1].strip().split(', ')))

    x1, y1 = p[0], p[1]
    slope = v[1] / v[0]

    intercept = y1 - (slope * x1)
    slopes.append(slope)
    intercepts.append(intercept)
    pos.append(p)
    vel.append(v)
    

count = 0
l = 200000000000000
r = 400000000000000
for i in range(len(slopes)):
    for j in range(i + 1, len(slopes)):
        if slopes[i] == slopes[j]:
            # print('neveeeer meeeaaant')
            continue

        x1, y1, x2, y2  = pos[i][0], pos[i][1], pos[j][0], pos[j][1]
        vx1, vy1, vx2, vy2 = vel[i][0], vel[i][1], vel[j][0], vel[j][1]
        
        intersec_x = (intercepts[i] - intercepts[j]) / (slopes[j] - slopes[i])
        intersec_y = (slopes[i] * intersec_x) + intercepts[i]

        if not (l < intersec_x < r and l < intersec_y < r):
            continue

        opp_vel_x_pos = (vx1 >= 0 and intersec_x < x1) or (vx2 >= 0 and intersec_x < x2)
        opp_vel_x_neg = (vx1 <= 0 and intersec_x > x1) or (vx2 <= 0 and intersec_x > x2)

        if opp_vel_x_pos or opp_vel_x_neg:
            continue

        opp_vel_y_pos = (vy1 >= 0 and intersec_y < y1) or (vy2 >= 0 and intersec_y < y2)
        opp_vel_y_neg = (vy1 <= 0 and intersec_y > y1) or (vy2 <= 0 and intersec_y > y2)

        if opp_vel_y_pos or opp_vel_y_neg:
            continue

        count += 1

print(count)
