import Link from 'next/link';
import { buttonVariants } from '@/components/ui/button'; // For consistent link styling

export default function Header() {
  return (
    <header className="bg-secondary text-secondary-foreground py-4 px-6 shadow-md">
      <nav className="container mx-auto flex justify-between items-center">
        <Link href="/" className="text-2xl font-bold hover:text-primary">
          C++ RefactorHub
        </Link>
        <div className="space-x-4">
          <Link href="/" className={buttonVariants({ variant: "ghost" })}>
            Home
          </Link>
          <Link href="/smells" className={buttonVariants({ variant: "ghost" })}>
            Code Smells
          </Link>
          {/* Linking to the first quiz as a placeholder for a quiz index page */}
          <Link href="/quizzes/long-method-quiz-1" className={buttonVariants({ variant: "ghost" })}>
            Quizzes
          </Link>
        </div>
      </nav>
    </header>
  );
}
