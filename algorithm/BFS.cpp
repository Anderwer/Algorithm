BFS模板

q.push(初始状态)
while(!q.empty()){
    a = q.front();
    q.pop();
    for(枚举a的所有可达状态v){
        if(本状态v合法){
            执行操作;
            q.push(v);
        }
    }
}
