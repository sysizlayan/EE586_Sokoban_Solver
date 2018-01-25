load('OnlyManhattan.mat')
max_steps = max(steps);
x = [];
y_mean = [];
y_min = [];
y_max = [];
max_count=-inf;

up_limit= 3e7;
for i=1:max_steps
    count = sum(steps==i);
    if(max_count<count)
        max_count=count;
    end
end
same_y =[];
for i=1:max_steps
    count = sum(steps==i);
    if(count ~= 0)
        same_y_i = zeros(1,max_count);
        same_y_i(1:count) = time(steps == i);
        same_y = [same_y;same_y_i];
        y_max_i = max(time(steps == i));
        y_min_i = min(time(steps == i));
        y_mean_i = sum(time(steps == i))/count;
        x = [x i];
        y_mean = [y_mean y_mean_i];
        y_min = [y_min, y_min_i];
        y_max = [y_max, y_max_i];
    end
end

indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
manhattanMax = ['max:(',num2str(round(ymax*1e-6,4)),')']

figure
plot(x,y_min,'o')
hold on
plot(x,y_mean)
hold on
plot(x,y_max,'o')
text(xmax,ymax,manhattanMax,'HorizontalAlignment','right');
legend('min','mean','max');

figure
subplot(1,5,1)
bar3(x,same_y,'stacked');
zlim([0 up_limit])
ylim([0 180])

zlabel('Elapsed Time(\mus)');
ylabel(sprintf('Optimal Solution Steps,%s s',manhattanMax));
title('ManhattanOnly')

hold on

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
load('OnlyDeadlock.mat')
max_steps = max(steps);
x = [];
y_mean = [];
y_min = [];
y_max = [];
max_count=-inf;
for i=1:max_steps
    count = sum(steps==i);
    if(max_count<count)
        max_count=count;
    end
end
same_y =[];
for i=1:max_steps
    count = sum(steps==i);
    if(count ~= 0)
        same_y_i = zeros(1,max_count);
        same_y_i(1:count) = time(steps == i);
        same_y = [same_y;same_y_i];
        y_max_i = max(time(steps == i));
        y_min_i = min(time(steps == i));
        y_mean_i = sum(time(steps == i))/count;
        x = [x i];
        y_mean = [y_mean y_mean_i];
        y_min = [y_min, y_min_i];
        y_max = [y_max, y_max_i];
    end
end

indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
deadlockMax = ['max:(',num2str(round(ymax*1e-6,4)),')']

subplot(1,5,2)
bar3(x,same_y,'stacked');
zlim([0 up_limit])
ylim([0 180])
zlabel('Elapsed Time(\mus)');
ylabel(sprintf('Optimal Solution Steps,%s s',deadlockMax));
title('DeadlockOnly')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
load('DeadlockAndManhattan.mat')
max_steps = max(steps);
x = [];
y_mean = [];
y_min = [];
y_max = [];
max_count=-inf;
for i=1:max_steps
    count = sum(steps==i);
    if(max_count<count)
        max_count=count;
    end
end
same_y =[];
for i=1:max_steps
    count = sum(steps==i);
    if(count ~= 0)
        same_y_i = zeros(1,max_count);
        same_y_i(1:count) = time(steps == i);
        same_y = [same_y;same_y_i];
        y_max_i = max(time(steps == i));
        y_min_i = min(time(steps == i));
        y_mean_i = sum(time(steps == i))/count;
        x = [x i];
        y_mean = [y_mean y_mean_i];
        y_min = [y_min, y_min_i];
        y_max = [y_max, y_max_i];
    end
end

indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
DLCandManhMax = ['max:(',num2str(round(ymax*1e-6,4)),')']

subplot(1,5,3)
bar3(x,same_y,'stacked');
zlim([0 up_limit])
ylim([0 180])

zlabel('Elapsed Time(\mus)');
ylabel(sprintf('Optimal Solution Steps,%s s',DLCandManhMax));
title('Deadlock&Manhattan')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
load('DeadlockCheckingBFS.mat')
max_steps = max(steps);
x = [];
y_mean = [];
y_min = [];
y_max = [];
max_count=-inf;
for i=1:max_steps
    count = sum(steps==i);
    if(max_count<count)
        max_count=count;
    end
end
same_y =[];
for i=1:max_steps
    count = sum(steps==i);
    if(count ~= 0)
        same_y_i = zeros(1,max_count);
        same_y_i(1:count) = time(steps == i);
        same_y = [same_y;same_y_i];
        y_max_i = max(time(steps == i));
        y_min_i = min(time(steps == i));
        y_mean_i = sum(time(steps == i))/count;
        x = [x i];
        y_mean = [y_mean y_mean_i];
        y_min = [y_min, y_min_i];
        y_max = [y_max, y_max_i];
    end
end

indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
DLCBfsMax = ['max:(',num2str(round(ymax*1e-6,4)),')']

subplot(1,5,4)
bar3(x,same_y,'stacked');
zlim([0 up_limit])
ylim([0 180])

zlabel('Elapsed Time(\mus)');
ylabel(sprintf('Optimal Solution Steps,%s s',DLCBfsMax));
title('Deadlock&BFS')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
load('OnlyEucDist.mat')
max_steps = max(steps);
x = [];
y_mean = [];
y_min = [];
y_max = [];
max_count=-inf;
for i=1:max_steps
    count = sum(steps==i);
    if(max_count<count)
        max_count=count;
    end
end
same_y =[];
for i=1:max_steps
    count = sum(steps==i);
    if(count ~= 0)
        same_y_i = zeros(1,max_count);
        same_y_i(1:count) = time(steps == i);
        same_y = [same_y;same_y_i];
        y_max_i = max(time(steps == i));
        y_min_i = min(time(steps == i));
        y_mean_i = sum(time(steps == i))/count;
        x = [x i];
        y_mean = [y_mean y_mean_i];
        y_min = [y_min, y_min_i];
        y_max = [y_max, y_max_i];
    end
end

indexmax = find(max(y_max) == y_max);
xmax = x(indexmax);
ymax = y_max(indexmax);
eucMax = ['max:(',num2str(round(ymax*1e-6,4)),')']

subplot(1,5,5)
bar3(x,same_y,'stacked');
zlim([0 up_limit])
ylim([0 180])

zlabel('Elapsed Time(\mus)');
ylabel(sprintf('Optimal Solution Steps,%s s',eucMax));
title('Euclidean')