int is_small_pic(int tag){
    switch(tag){
        case 116:
        case 117:
        case 122:
        case 123:
        case 126:
        case 127:
        return 1;
    }
    if(tag >= 401 && tag < 412){
        return 1;
    }
    return 0;
}