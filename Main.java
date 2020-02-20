class Main {
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
        }
    }