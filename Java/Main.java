import java.util.*;
class Main {
    public static void starTriangle(int n){
        for(int i = 0; i < n; i++){
          String s = "*";
          for(int j = 0; j < i; j++){
            s = s + "*";
          }
          System.out.println(s);
        }
      }
        public static void main(String[] args) {
            //part 1
            Container<String> cs = new Container<>();
            cs.set("hello I am a string");
            System.out.println(cs.get());
            Container<Integer> ci = new Container<>();
            ci.set(42);
            System.out.println(ci.get());

            //part 2
            Shape shape;
            shape = new Triangle();
            System.out.println(shape.points());

            Shape shape2;
            shape2 = new Square();
            System.out.println(shape2.points());

            //part 3
            starTriangle(6);

            //part4
            ArrayList<Integer> alist = new ArrayList<Integer>();
            alist.add(12);
            alist.add(3);
            alist.add(17);
            Collections.sort(alist);
            Iterator<Integer>  iter = alist.iterator();
            System.out.println("alist :");
            while(iter.hasNext()){
              System.out.println(iter.next());
            }

            Stack<Integer> stack = new Stack<Integer>();
            stack.push(1);
            stack.push(4);
            stack.push(2);
            Collections.sort(stack);
            Iterator<Integer> iter2 = stack.iterator();
            System.out.println("stack :");
            while(iter2.hasNext()){
              System.out.println(iter2.next());
            }
        }
    }