clc
clear

up_to_what = 170;
time = ones(1,up_to_what);
steps = zeros(1,up_to_what);

for i = 1:up_to_what
    command = sprintf('ee586.exe pufi%d.txt o',i);
    status = system(command);
    fileID = fopen('result.txt');
    A = fscanf(fileID,'%d\n');
    time(i) = A(1);
    steps(i) = A(2);
    fclose(fileID);
    display(i);
end
clear command
clear status
clear A
clear fileID
clear up_to_what
clear ans
clear i
save('DeadlockAndManhattan.mat')