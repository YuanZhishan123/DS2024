#include"Stack.cpp"
#include<cstdlib> 
#include<ctime>
int areaCalcu(Vector<int>&heights) {    
        Stack<int> s; // 定义一个栈来存储索引  
        int maxArea = 0; // 初始化最大面积为0  
        heights.insert(-1); // 在高度数组末尾添加一个-1，确保所有元素都能被处理  
  
        for (int i = 0; i < heights.size(); i++) { // 遍历高度数组  
            while (!s.empty() && heights[i] < heights[s.top()]) { // 当栈不为空且当前高度小于栈顶索引对应的高度时  
                int itop = s.top(); // 获取栈顶索引  
                s.pop(); // 弹出栈顶元素  
                int left = s.empty() ? -1 : s.top(); // 计算当前矩形左边界的索引  
                maxArea = max(maxArea, (i - left - 1) * heights[itop]); // 更新最大面积  
            }  
            s.push(i); // 将当前索引压入栈中  
        }  
  
        return maxArea; // 返回最大矩形面积  
    }  
main(){
	int recnum;
	Vector<int> rec,rec0;
	srand(time(NULL));
	for(int i=0;i<10;i++){
		recnum=1+rand()%105;
		cout<<"第"<<i<<"组共有"<<recnum<<"个矩形"<<"高度分别为";
		for(int k=0;k<recnum;k++){
			rec.insert(rand()%104);
			cout<<rec[k]<<' ';
		}
		cout<<endl;
		cout<<"第"<<i<<"组矩形的最大面积为"<<areaCalcu(rec)<<endl;
		rec=rec0; 
		
	}
}
