clc
clear
load pufiban.mat
temp = [];
file_index = 1;
for i=1:length(Pufiban)
    tmp_str = Pufiban{i};
    if(strcmp(tmp_str,"Author: Jordi Domenech"))
        fileID = fopen(sprintf('pufi%d.txt',file_index),'w');
        file_index = file_index+1;
        sizee = size(temp);
        rows = sizee(1);
        columns = 0;
        for j=1:rows
            if(columns<length(char(temp(j))))
                columns = length(char(temp(j)));
            end
        end        
        fprintf(fileID,'%d %d\r\n',rows,columns);
        for j=1:rows
            temp_char = char(temp(j));
            if(length(temp_char)<columns)
                temp_char = [temp_char ones(1,columns-length(temp_char))*' '];
            end
            
            fprintf(fileID,'%s\r\n',convertCharsToStrings(temp_char));
        end
        fclose(fileID);
        temp = [];
    elseif(~contains(tmp_str,'Title:') && ~contains(tmp_str,'Limit:'))
        temp = [temp; tmp_str]; 
    end
    
end