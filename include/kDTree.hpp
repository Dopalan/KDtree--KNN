#include "main.hpp"
#include "Dataset.hpp"


struct kDTreeNode
{
    vector<int> data;
    int label;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = 0;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(vector<int> data, int label, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = label;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~kDTreeNode()
    {
        this->left = nullptr;
        this->right = nullptr;
        data.clear();
    }
    void dele(){
        this->left = nullptr;
        this->right = nullptr;
        data.clear();
    }

    void print() const
    {
        cout << "(";
        for(int i = 0; i < data.size(); i++)
        {
            cout << data[i];
            if (i == data.size() - 1) cout << ")";
            else cout << ",";
        }
        cout << " ";
    }

    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;
    int count;
private:
public:


    //tạo, hủy
    kDTree(int k = 2){
        this->k = k;
        this->root = nullptr;
        this->count = 0;
    }
    ~kDTree(){
        this->k = 0;
        this->count = 0;
        clear(root); 
    }
    
     void clear(const kDTreeNode* temp) {
        if (temp == nullptr) {
            return;
        }

        clear(temp->left); 
        clear(temp->right);
        delete temp;
    }
    
    //chỉnh giá trị k
    void upK(int k){
        this->k = k;
    }
    int getK(){
        return this->k;
    }

    //copy
    kDTreeNode* copy(const kDTreeNode* temp) {
        if (temp == nullptr) {
            return nullptr;
        }

        kDTreeNode* newNode = new kDTreeNode(temp->data, copy(temp->left), copy(temp->right));
        return newNode;
    }

    const kDTree &operator=(const kDTree &other){
        this->k = other.k;
        this->root = copy(other.root);
        this->count = other.count;
        
        return *this;
    }
    
    kDTree(const kDTree &other){
        this->k = other.k;
        this->root = copy(other.root);
        this->count = other.count;
    }



    //số lượng Node
    int nodeCount() const {
        return nodeCount(root);
    }

    int nodeCount(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        return nodeCount(node->left) + nodeCount(node->right) + 1;
    }

    //chiều cao
    int height() const{
        return height(root);
    }

    int height(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;  
        }

        int lHeight = height(node->left);
        int rHeight = height(node->right);

        return max(lHeight, rHeight) + 1;
    }


    //Leaf Node  
    int leafCount() const {
        return leafCount(root);
    }

    int leafCount(const kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        return leafCount(node->left) + leafCount(node->right);
    }



    void inorderTraversal() const {
        inorder(root);
    }

    void inorder(const kDTreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);
        cout <<*node<<" ";
        inorder(node->right);
    }


    void preorderTraversal() const {
        preorder(root);
    }



    void preorder(const kDTreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        cout <<*node<<" ";
        preorder(node->left);
        preorder(node->right);
    }



    void postorderTraversal() const {
        postorder(root);
    }

    void postorder(const kDTreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        postorder(node->left);
        postorder(node->right);
        cout <<*node<<" ";
    }

    //chèn
    void insert(const vector<int> &point) {
        root = insert(root, point, 0);
        this->count++;
    }

    kDTreeNode* insert(kDTreeNode* node, const vector<int> &point, int level) {
        if (node == nullptr) {
            return new kDTreeNode(point);
        }

        int alpha = level % k;
        if (point[alpha] < node->data[alpha]) {
            node->left = insert(node->left, point, level + 1);
        } else {
            node->right = insert(node->right, point, level + 1);
        }

        return node;
    }


    void remove(const vector<int> &point) {
        root = remove(root, point, 0);
    }

    kDTreeNode* remove(kDTreeNode* node, const vector<int> &point, int level) {

        if (node == nullptr) {
            return nullptr;
        }

        int alpha = level % k;

        if (point[alpha] < node->data[alpha]) {
            node->left = remove(node->left, point, level + 1);
        } else if (point[alpha] > node->data[alpha]) {
            node->right = remove(node->right, point, level + 1);
        } else {
            for(int i = 0; i < k; i++){
                if (point[i] != node->data[i] ){
                    node->left = remove(node->left, point, level + 1);
                    node->right = remove(node->right, point, level + 1);
                    return node;
                }
            }
            if (node->right != nullptr) {
               node->data = findMin(node->right, alpha);
               
               node->right = remove(node->right, node->data, level + 1);
               

            } else if (node->left != nullptr) {
                node->data = findMin(node->left, alpha);
                node->right = remove(node->left, node->data, level + 1);
                delete node->left;
                
            } else{
                //node = nullptr;
                //node->left = nullptr;
                //node->right = nullptr;
                //node->data.clear();
                delete node;
               
            }

        }

        return node;
    }

    vector<int> findMin(kDTreeNode* node, int alpha) {

        if (node->left == nullptr && node->right == nullptr) {
            return node->data;
        }
        
        vector<int> minx,temp;
        minx = node->data;

        if (node->left != nullptr){
            temp = findMin(node->left, alpha);
            minx = minx[alpha] <= temp[alpha] ? minx : temp;
        }

        if (node->right != nullptr){
            temp = findMin(node->right, alpha);
            minx = minx[alpha] <= temp[alpha] ? minx : temp;
        }

        return minx;
        
    }    
    

    //tìm kiếm
    bool search(const vector<int> &point) {
        return search(root, point, 0);
    }

    bool search(kDTreeNode* node, const vector<int> &point, int level) {
        if (node == nullptr) {
            return false;
        }

        int alpha = level % k;
        if (point[alpha] < node->data[alpha]) {
            return search(node->left, point, level + 1);
        } else if (point[alpha] > node->data[alpha]) {
            return search(node->right, point, level + 1);
        } else {
            for(int i = 0; i < k; i++){
                if (point[i] != node->data[i] ){
                    bool t;
                    return search(node->left, point, level + 1) || search(node->right, point, level + 1);
                    
                    
                }
            }

            return true;
        }
    }

    //xây dụng cây từ mảng đầu vào
    void buildTree(const vector<vector<int>> &pointList) {

        vector<vector<int>> tempList(pointList.size());
        for (int i = 0; i < pointList.size(); i++) {
            tempList[i] = pointList[i];
        }

        root = buildTree(tempList, 0);
        tempList.clear();
    }

   kDTreeNode* buildTree(  vector<vector<int>> pointList, int level) {
        if (pointList.empty()) {
            return nullptr;
        }

        int alpha = level % k;

        MmergeSort(pointList, 0, pointList.size() - 1, alpha);
        int mid = (pointList.size()-1) / 2;
        
        while(mid - 1 >=0 && pointList[mid][alpha] == pointList[mid-1][alpha] ){
            mid--;
        }
        
        kDTreeNode* node = new kDTreeNode(pointList[mid]);
        node->left = buildTree(vector<vector<int>>(pointList.begin(), pointList.begin() + mid ), level + 1);
        node->right = buildTree(vector<vector<int>>(pointList.begin() + mid + 1, pointList.end()), level + 1);

        return node;
    }


    void buildTreeLabel(const vector<vector<int>> &pointList, const vector<int> & label){
        this->count = pointList.size();

        vector<vector<int>> tempList(pointList.size());
        for (int i = 0; i < pointList.size(); i++) {
            tempList[i] = pointList[i];
        }
        vector<int> tempLabel = label;
        this->root = this->buildTreeLabel(tempList, tempLabel, 0);
        tempList.clear();
        tempLabel.clear();
    }

    kDTreeNode* buildTreeLabel(  vector<vector<int>> pointList, vector<int>  label, int level){


        if (pointList.empty()) {
            return nullptr;
        }

        int alpha = level % k;

        Label_mergeSort(pointList, label, 0, pointList.size() - 1, alpha);
        int mid = (pointList.size()-1) / 2;
        
        while(mid - 1 >=0 && pointList[mid][alpha] == pointList[mid-1][alpha] ){
            mid--;
        }
        kDTreeNode* node = new kDTreeNode(pointList[mid],label[mid]);

        node->left = buildTreeLabel(vector<vector<int>>(pointList.begin(), pointList.begin() + mid ),vector<int> (label.begin(), label.begin() + mid ), level + 1);
        node->right = buildTreeLabel(vector<vector<int>>(pointList.begin() + mid + 1, pointList.end()),vector<int> (label.begin() + mid + 1, label.end()), level + 1);

        return node;
        
    }

    void Label_Mmerge(vector<vector<int>>& pointList,  vector<int> & label, int left, int mid, int right, int compareIndex){
        int n1 = mid - left + 1; 
        int n2 = right - mid; 
        vector<vector<int>> L(pointList.size());
        vector<vector<int>> R(pointList.size());

        vector<int> L_label(label.size());
        vector<int> R_label(label.size());

        for (int i = 0; i < n1; i++) {
            L[i] = pointList[left + i];
            L_label[i] = label[left + i];
        }
        

        for (int j = 0; j < n2; j++) {
            R[j] = pointList[mid + 1 + j];
            R_label[j] = label[mid + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (L[i][compareIndex] <= R[j][compareIndex]) {
                pointList[k] = L[i];
                label[k] = L_label[i];
                i++;
            } else {
                pointList[k] = R[j];
                label[k] = R_label[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            pointList[k] = L[i];
            label[k] = L_label[i];
            i++;
            k++;
        }

        while (j < n2) {
            pointList[k] = R[j];
            label[k] = R_label[j];
            j++;
            k++;
        }
    }



    void Label_mergeSort(vector<vector<int>>& pointList,  vector<int> & label, int left, int right, int compareIndex){
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;

        Label_mergeSort(pointList, label, left, mid, compareIndex);
        Label_mergeSort(pointList,label, mid + 1, right, compareIndex);

        Label_Mmerge(pointList, label, left, mid, right, compareIndex);
    }


    void nearestNeighbour(const vector<int> &target, kDTreeNode*& best) {
        best = nullptr;
        recNearestNeighbour(root, target, best, 0);
    }  

    void recNearestNeighbour(kDTreeNode* temp, const vector<int> &target, kDTreeNode*& best, int level) {
        if (temp == nullptr ) {
            return;
        }
        if (best == nullptr && temp->left == nullptr && temp->right == nullptr) {
            best = temp;
            return;
        }

        int alpha = level % k;
        int check = 0;
        if (target[alpha] < temp->data[alpha]) {
             recNearestNeighbour(temp->left, target, best, level + 1);
             check = 0;
        } else {
             recNearestNeighbour(temp->right, target, best, level + 1);
             check = 1;
        }
        if (best == nullptr) {
            best = temp;
        }
        double r = distance(temp->data, target);
        double R = distance(best->data, target);

         if (R > r ) {
            best = temp;
            R = r;
        }

        if(R == 0) return;
        double d = abs(target[alpha] - temp->data[alpha]);

        if(check  == 1 && d < R && temp->left!= nullptr){
            recNearestNeighbour(temp->left, target, best, level + 1);
        }

        if(check  == 0 && d < R && temp->right!= nullptr){
            recNearestNeighbour(temp->right, target, best, level + 1);
        }
    
        return;
    }



    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList){
        bestList.clear();
        
        recKNearestNeighbour(root, target, k, bestList, 0);
    }



    void recKNearestNeighbour(kDTreeNode* temp, const vector<int>& target, int k, vector<kDTreeNode*>& bestList, int level) {
        if (temp == nullptr) {
            return;
        }
        int alpha = level % this->k;

        
        int check = -1;
        if (target[alpha] < temp->data[alpha] ) {
            check = 0;
             recKNearestNeighbour(temp->left, target, k, bestList, level + 1);
        } else {
                check = 1;
                recKNearestNeighbour(temp->right, target,k, bestList, level + 1);     
        }    
        
        
        
        double r = distance(temp->data, target); 
        double R = 100000;
        if ( bestList.size() < k) {
            bestList.push_back(temp);
            sortBestList(bestList, target);
            R =  distance(bestList.back()->data, target);
        }else{
            R =  distance(bestList.back()->data, target);
            if (R > r ) {
                bestList.pop_back();
                bestList.push_back(temp);
                sortBestList(bestList, target);
                R =  distance(bestList.back()->data, target);
            }
        }
            
        //if(R == 0) return;
        double d = abs(target[alpha] - temp->data[alpha]);

        if( check  == 1 &&  (d < R || bestList.size() < k) && temp->left!= nullptr)  {
            recKNearestNeighbour(temp->left, target, k,bestList, level + 1);
        }
        
        if( check  == 0 && ( d < R || bestList.size() < k ) && temp->right!= nullptr ){
            recKNearestNeighbour(temp->right, target, k,bestList, level + 1);
        }
    
        return;
}




    double distance(const vector<int>& a, const vector<int>& b) {
        double r = 0;
        for (int i = 0; i < a.size() && i < b.size(); i++) {
            r += pow(a[i] - b[i], 2);
        }
        return sqrt(r);
    }

  

    void sortBestList(vector<kDTreeNode*>& bestList, const vector<int>& target) {
        if (bestList.size() < 2) return;
        kDTreeNode* lastNode = bestList.back();
        bestList.pop_back();

        //R lớn, R lớn nhất tính tới thời điểm hiện tại. R này của node cuối, Node cách xa nhất
        double R = distance(lastNode->data, target);

        //chạy vòng for để xét
        for (vector<kDTreeNode*>::iterator it = bestList.begin(); it != bestList.end(); ++it) {
            double r = distance((*it)->data, target);
            if (r > R) {
                bestList.insert(it, lastNode);
                return;
            }
        }

        
        bestList.push_back(lastNode);
    }
    
     void Mmerge(vector<vector<int>>& pointList, int left, int mid, int right, int compareIndex) {

        int n1 = mid - left + 1; 
        int n2 = right - mid; 
        vector<vector<int>> L(pointList.size());
        vector<vector<int>> R(pointList.size());


        for (int i = 0; i < n1; i++) {
            L[i] = pointList[left + i];
        }
        

        for (int j = 0; j < n2; j++) {
            R[j] = pointList[mid + 1 + j];
        }
        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (L[i][compareIndex] <= R[j][compareIndex]) {
                pointList[k] = L[i];
                i++;
            } else {
                pointList[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            pointList[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            pointList[k] = R[j];
            j++;
            k++;
        }
    }
    void MmergeSort(vector<vector<int>>& pointList, int left, int right, int compareIndex) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;

        MmergeSort(pointList, left, mid, compareIndex);
        MmergeSort(pointList, mid + 1, right, compareIndex);

        Mmerge(pointList, left, mid, right, compareIndex);
    }
    

};


class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    kDTree  kdtree;
public:
    kNN(int k = 5){
        this->k = k;
        X_train = nullptr;
        y_train = nullptr;
    }
    void fit(Dataset &X_train, Dataset &y_train)
    {
            this->X_train = &X_train;
            this->y_train = &y_train;
            if(X_train.data.size()){
                int dimension = X_train.data.front().size();
                kdtree.upK(dimension);
            }
            
            vector<vector<int>> pointList;
            for (const auto& innerList : this->X_train->data) {
                    pointList.push_back({innerList.begin(), innerList.end()});
            }

           
            vector<int>  label;
            for (const auto& t : this->y_train->data) {
                label.push_back(t.front());
                
            }
            /*vector<int>  label;
            label.reserve(temp.size() * temp[0].size()); 
            for (const auto& t : temp) {
                label.insert(label.end(), t.begin(), t.end()); 
                
            }*/
            kdtree.buildTreeLabel(pointList, label);
            pointList.clear();
            label.clear();
            //test

            /*freopen("out.txt", "w", stdout);
            cout<<endl<<"111"<<endl;
            cout<<X_train.data.front().size()<<endl;
            cout<<kdtree.getK()<<endl;
            X_train.printHead(10,1000);
            cout<<endl<<endl;*/

            /*for(int i = 0; i <= 10; i++ ){
                for(int j = 0; j < kdtree.getK() - 1; j++){
                    cout<<pointList[i][j]<<" ";
                }
                cout<<pointList[i][kdtree.getK()-1];
                cout<<endl;
            }*/
            


            //test
           /* freopen("out.txt", "w", stdout);
            y_train.printHead(1000,2);
            cout<<endl<<"_-------------------------------"<<endl;
            for(int i = 0; i < label.size(); i++){
                cout<<label[i]<<endl;
            }*/
        
    }       

    //kết quả là mảng được đoán
    Dataset predict(Dataset &X_test){
        
        Dataset result;
        result.columnName.push_back("label");
        if(X_test.data.size() == 0){
            return result;
        } 
        
        //mỗi một list của X là một target, so target với mảng đã tạo từ trước, predList là mảng kết quả của mỗi lần 1 target
        for (const auto& innerList : X_test.data) {

            vector<int> count(20, 0);
            vector<kDTreeNode*> predList;
            kdtree.kNearestNeighbour({innerList.begin(), innerList.end()}, k, predList);
            for(const auto& ppredList : predList){
                count[ppredList->label]++;
            }
            predList.clear();
            //biến phụ, vòng for để tìm ra label xuất hiện nhiều nhất
            int maxxPred = -10, rePred = 0;
            for(int i = 0; i < 10; i++){
                if(count[i] > maxxPred){
                    maxxPred = count[i];
                    rePred = i;
                }
            }

            result.data.push_back({rePred});


        }

         return result;
    }


    double score(const Dataset &y_test, const Dataset &y_pred){
        if(y_test.data.size() == 0 || y_pred.data.size() == 0 || y_test.data.size()!= y_test.data.size()){
                return NAN;
            } 
        
        vector<int>  label_test,label_pred;
        for (const auto& t : y_test.data) {
            label_test.push_back(t.front());
                
        }

        for (const auto& t : y_pred.data) {
            label_pred.push_back(t.front());
                
        }
        int n = label_pred.size(), count = 0;
        for(int i = 0; i < n; i++){
            //cout<<label_pred[i]<<"  "<<label_test[i]<<" "<<count<<endl;
            if(label_pred[i] == label_test[i]) count++;
        }
        label_test.clear();
        label_pred.clear();
        //y_test.printHead();
        //y_pred.printHead();
        double result = (double) count / (double) n;
        return result;
    }



  
};
