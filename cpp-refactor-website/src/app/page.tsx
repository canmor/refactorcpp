import Link from 'next/link';
import { Button } from '@/components/ui/button';
import { Card, CardHeader, CardTitle, CardDescription, CardContent } from '@/components/ui/card';

export default function HomePage() {
  return (
    <div className="flex flex-col items-center justify-center text-center">
      <Card className="w-full max-w-2xl">
        <CardHeader>
          <CardTitle className="text-4xl font-bold mb-4">Welcome to C++ RefactorHub!</CardTitle>
          <CardDescription className="text-lg text-muted-foreground mb-8">
            Your interactive guide to understanding and refactoring C++ code smells. 
            Learn to write cleaner, more maintainable C++ code.
          </CardDescription>
        </CardHeader>
        <CardContent className="flex flex-col sm:flex-row justify-center gap-4">
          <Link href="/smells" passHref>
            <Button size="lg" className="w-full sm:w-auto">Explore Code Smells</Button>
          </Link>
          <Link href="/quizzes" passHref>
            <Button size="lg" variant="outline" className="w-full sm:w-auto">Test Your Knowledge</Button>
          </Link>
        </CardContent>
      </Card>

      <section className="mt-12 w-full max-w-4xl text-left">
         <h2 className="text-2xl font-semibold mb-4 text-center">Features</h2>
         <div className="grid md:grid-cols-2 gap-6">
             <Card>
                 <CardHeader>
                     <CardTitle>Comprehensive Smell Library</CardTitle>
                 </CardHeader>
                 <CardContent>
                     <p>Detailed explanations of common C++ code smells with practical before & after examples.</p>
                 </CardContent>
             </Card>
             <Card>
                 <CardHeader>
                     <CardTitle>Interactive Quizzes</CardTitle>
                 </CardHeader>
                 <CardContent>
                     <p>Reinforce your learning with coding quizzes designed to test your understanding of each smell.</p>
                 </CardContent>
             </Card>
         </div>
      </section>
    </div>
  );
}
