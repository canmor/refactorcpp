"use client";

import { useState } from 'react';
import { QuizData, QuizOption } from '@/lib/quizDataLoader'; // Assuming QuizOption is exported
import { Button } from '@/components/ui/button';
import { RadioGroup, RadioGroupItem } from '@/components/ui/radio-group';
import { Label } from '@/components/ui/label'; // For RadioGroup
import { Alert, AlertDescription, AlertTitle } from '@/components/ui/alert';
import { CheckCircle, XCircle, Info } from 'lucide-react'; // Icons for feedback

interface QuizClientComponentProps {
  quiz: QuizData;
}

export default function QuizClientComponent({ quiz }: QuizClientComponentProps) {
  const [selectedAnswer, setSelectedAnswer] = useState<string | null>(null);
  const [isSubmitted, setIsSubmitted] = useState(false);
  const [isCorrect, setIsCorrect] = useState<boolean | null>(null);

  const handleSubmit = () => {
    if (!selectedAnswer) return;
    setIsSubmitted(true);
    setIsCorrect(selectedAnswer === quiz.correctAnswer);
  };

  const getOptionText = (optionId: string): string => {
     const option = quiz.options.find(opt => opt.id === optionId);
     return option ? option.text : "Unknown option";
  };

  return (
    <div className="max-w-2xl mx-auto">
      <h1 className="text-3xl font-bold mb-4">{quiz.title}</h1>
      <p className="text-lg mb-4">{quiz.question}</p>

      {quiz.codeSnippet?.html && (
        <div
          className="bg-gray-900 text-white p-4 rounded-md mb-6 overflow-x-auto shiki-container" // Add a class for shiki styles if needed
          dangerouslySetInnerHTML={{ __html: quiz.codeSnippet.html }}
        />
      )}

      <div className="mb-6">
        <RadioGroup
          value={selectedAnswer || ""}
          onValueChange={(value) => !isSubmitted && setSelectedAnswer(value)}
          disabled={isSubmitted}
        >
          {quiz.options.map((option) => (
            <div key={option.id} className="flex items-center space-x-2 mb-2 p-3 rounded-md border border-input hover:bg-accent">
              <RadioGroupItem value={option.id} id={`option-${option.id}`} />
              <Label htmlFor={`option-${option.id}`} className="flex-1 cursor-pointer">{option.text}</Label>
            </div>
          ))}
        </RadioGroup>
      </div>

      {!isSubmitted && (
        <Button onClick={handleSubmit} disabled={!selectedAnswer || isSubmitted}>
          Submit Answer
        </Button>
      )}

      {isSubmitted && isCorrect !== null && (
        <Alert variant={isCorrect ? "default" : "destructive"} className={`mt-6 ${isCorrect ? 'border-green-500' : 'border-red-500'}`}>
          {isCorrect ? <CheckCircle className="h-5 w-5 text-green-500" /> : <XCircle className="h-5 w-5 text-red-500" />}
          <AlertTitle className={isCorrect ? "text-green-700" : "text-red-700"}>
            {isCorrect ? "Correct!" : "Incorrect"}
          </AlertTitle>
          <AlertDescription>
            {isCorrect ? quiz.explanation : (
              <>
                Your answer: "{getOptionText(selectedAnswer!)}" was incorrect. <br />
                Correct answer: "{getOptionText(quiz.correctAnswer)}". <br />
                <strong>Explanation:</strong> {quiz.explanation}
              </>
            )}
          </AlertDescription>
        </Alert>
      )}
    </div>
  );
}
