load('DeadlockAndManhattan.mat')
x= steps(1);
y_mean= [];
y_min = [];
y_max = [];
% same_stepped_values = [];
prev = steps(1);
sum = 0;
number_of_same_steps = 0;
local_min = time(1);
local_max = time(1);
for i=1:length(steps)
    if(prev~=steps(i))
        y_mean =[y_mean sum/number_of_same_steps];
        y_min = [y_min local_min];
        y_max = [y_max local_max];
        local_min = time(i);
        local_max = time(i);
        number_of_same_steps = 1;
        x = [x steps(i)];
        prev = steps(i);
        sum = time(i);
    else
        number_of_same_steps = number_of_same_steps +1;
        sum = sum + time(i);
        if(local_min>time(i))
            local_min = time(i);
        end
        if(local_max<time(i))
            local_max = time(i);
        end
    end
end
y_mean =[y_mean time(end)];
y_min = [y_min time(end)];
y_max = [y_max time(end)];

% [global_max,Imax] = max(y_max);
% txt_max = sprintf("\\rightarrow %d",global_max);
indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
strmax = ['Maximum:',num2str(ymax), ' Step:',num2str(xmax)];

figure
% plot(x,y_min,'o')
hold on
plot(x,y_mean)
hold on
% plot(x,y_max,'o')

text(xmax,ymax,strmax,'HorizontalAlignment','right');
% text(Imax,global_max,txt_max);
legend('min','mean','max');