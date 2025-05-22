// src/app/quizzes/[quizId]/page.tsx
import { notFound } from 'next/navigation';
import { getQuizData, getAllQuizIds, QuizData } from '@/lib/quizDataLoader';
import QuizClientComponent from './QuizClientComponent'; // To be created next

export async function generateStaticParams() {
  const quizIds = await getAllQuizIds();
  return quizIds.map(id => ({ quizId: id }));
}

interface QuizPageProps {
  params: {
    quizId: string;
  };
}

export default async function QuizPage({ params }: QuizPageProps) {
  const quiz: QuizData | null = await getQuizData(params.quizId);

  if (!quiz) {
    notFound();
    return;
  }

  return (
    <div className="container mx-auto p-4">
      <QuizClientComponent quiz={quiz} />
    </div>
  );
}
