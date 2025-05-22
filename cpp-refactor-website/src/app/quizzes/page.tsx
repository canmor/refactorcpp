import Link from 'next/link';
import { Card, CardHeader, CardTitle, CardContent } from '@/components/ui/card';
import { getAllQuizIds, getQuizData } from '@/lib/quizDataLoader';

export const metadata = {
  title: 'C++ Refactoring Quizzes',
  description: 'Test your knowledge of C++ code smells and refactoring techniques',
};

export default async function QuizzesPage() {
  // Get all quiz IDs
  const quizIds = await getAllQuizIds();
  
  // Get the complete data for all quizzes to display more information
  const quizzes = await Promise.all(
    quizIds.map(async (quizId) => {
      const quiz = await getQuizData(quizId);
      return quiz;
    })
  );

  // Filter out any null values in case some quizzes couldn't be loaded
  const validQuizzes = quizzes.filter(quiz => quiz !== null);

  return (
    <div className="container mx-auto py-8 px-4">
      <h1 className="text-3xl font-bold mb-6">C++ Code Smell Quizzes</h1>
      <p className="mb-8 text-lg">
        Test your knowledge of code smells and refactoring techniques with these interactive quizzes.
      </p>
      
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
        {validQuizzes.map((quiz) => (
          <Link href={`/quizzes/${quiz.id}`} key={quiz.id}>
            <Card className="h-full transition-all hover:shadow-md hover:scale-[1.01]">
              <CardHeader>
                <CardTitle>{quiz.title}</CardTitle>
              </CardHeader>
              <CardContent>
                <p className="text-sm text-gray-500">
                  Related to: {quiz.smellId.split('-').map(word => 
                    word.charAt(0).toUpperCase() + word.slice(1)
                  ).join(' ')}
                </p>
              </CardContent>
            </Card>
          </Link>
        ))}
      </div>
      
      {validQuizzes.length === 0 && (
        <div className="text-center py-12">
          <p>No quizzes are currently available. Check back soon!</p>
        </div>
      )}
    </div>
  );
}
